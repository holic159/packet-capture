#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "packetdata.h"
#include <iostream>
#include <cstring>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList horzHeaders;
    ui->packetTable->setColumnCount(7);
    horzHeaders<<"Source MAC"<<"Destination MAC"<<"Source IP"<<"Source Port"<<"Destination IP"<<"Destination Port"<<"Packet Size";
    ui->packetTable->setHorizontalHeaderLabels(horzHeaders);
    ui->packetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);                        // read only
    for(int i=0;i<7;i++){
        ui->packetTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);     // qtablewidget auto sizing
    }
    ui->packetTable->connect(ui->packetTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellDoubleClick(int, int)));  // cell doubleclick event connect

    packetData = new PacketdataList();
    m_thread = new CaptureThread(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete packetData;
    delete m_thread;
}

void MainWindow::on_packet_capture(const bpf_u_int32 packet_size, char* source_mac, char* destination_mac, in_addr source_ip, short unsigned int source_port, in_addr destination_ip, short unsigned int destination_port,  const u_char* packet)

{
    int temp = ui->packetTable->rowCount();
    ui->packetTable->setRowCount(temp+1);
    ui->packetTable->setItem(temp, 0, new QTableWidgetItem(source_mac));                        // print Sourc MAC Address
    ui->packetTable->setItem(temp, 1, new QTableWidgetItem(destination_mac));                   // print Destination MAC Address
    ui->packetTable->setItem(temp, 2, new QTableWidgetItem(inet_ntoa(source_ip)));              // print Source IP
    ui->packetTable->setItem(temp, 3, new QTableWidgetItem(tr("%1").arg(source_port)));         // print Source Port
    ui->packetTable->setItem(temp, 4, new QTableWidgetItem(inet_ntoa(destination_ip)));         // print Destination IP
    ui->packetTable->setItem(temp, 5, new QTableWidgetItem(tr("%1").arg(destination_port)));    // print Destination Port
    ui->packetTable->setItem(temp, 6, new QTableWidgetItem(tr("%1").arg(packet_size)));         // print packet size
    packetData -> save_packet(packet);
/*  cli packet information
    cout << "=================================================================="<< endl;

    cout << "Packet Size is " << dec << packet_size << " Byte" << endl;    // print packet size
    cout << "Source MAC address\t\t->\t" << source_mac << endl;            // print Sourc MAC Address
    cout << "Destination MAC address\t->\t" << destination_mac << endl;    // print Destination MAC Address
    cout << "Source IP:Port\t\t->\t" << inet_ntoa(source_ip) << ":" << source_port << endl;                // print Source IP
    cout << "Destination IP:Port\t\t->\t" << inet_ntoa(destination_ip)<< ":" << destination_port << endl;  // print Destination IP

    cout << "=================================================================="<< endl;
*/
}


void MainWindow::run_button_click()
{
    m_thread->start();
    ui->currentStatusValue->setText("Capturing");
    ui->currentStatusValue->setStyleSheet("QLabel { color : green; }");
}

void MainWindow::stop_button_click()
{
    m_thread->terminate();
    m_thread->wait();
    ui->currentStatusValue->setText("Stop");
    ui->currentStatusValue->setStyleSheet("QLabel { color : red; }");
}

void MainWindow::cellDoubleClick(int row, int column)
{
    int packetSize = ui->packetTable->item(row, 6)->text().toInt();
    size_t offset = 0;
    size_t buf16Len;
    char buf16[16];
    char temp_buffer[200];
    int temp = packetSize;

    ui->packetData->setText("");                                // reset

    while(1){
        temp-=16;
        if(temp < -15) break;
        else if(temp <= 0) buf16Len = temp+16;
        else buf16Len = 16;
        strncpy(buf16, (const char*)packetData->get_packet(row)+offset, buf16Len);

        sprintf(temp_buffer, "%08X:  ", offset);                   // print offset

        ui->packetData->insertPlainText (temp_buffer);

        for (int i = 0; i < (int) buf16Len; i++) {
          if (i == 8) ui->packetData->insertPlainText(" ");
          sprintf(temp_buffer, "%02X ", (unsigned char) buf16[i]);
          ui->packetData->insertPlainText(temp_buffer);
        }

        for (int i = 0; i <= (16 - (int) buf16Len) * 3; i++)
          ui->packetData->insertPlainText(" ");
        if (buf16Len < 9) ui->packetData->insertPlainText("  ");


        for (int i = 0; i < (int) buf16Len; i++) {
          if (buf16[i] >= 0x20 && buf16[i] <= 0x7E){
            sprintf(temp_buffer, "%c", buf16[i]);
            ui->packetData->insertPlainText(temp_buffer);
          }
          else ui->packetData->insertPlainText(".");
        }

        offset += 16;                                           // add offset
        ui->packetData->insertPlainText("\n");

    }


    //packetData -> get_packet(row)
    //cout << packetSize << endl;
}

