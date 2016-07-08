#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

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
    for(int i=0;i<7;i++){
        ui->packetTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    CaptureThread* m_thread;
    m_thread = new CaptureThread(this);
    m_thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_packet_capture(const bpf_u_int32 packet_size, char* source_mac, char* destination_mac, in_addr source_ip, short unsigned int source_port, in_addr destination_ip, short unsigned int destination_port)

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
