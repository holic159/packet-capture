#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "capturethread.h"
#include "packetdata.h"
#include <pcap.h>
#include <arpa/inet.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    PacketdataList * packetData;
public:
    CaptureThread* m_thread;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void on_packet_capture(const bpf_u_int32 packet_size, char* source_mac, char* destination_mac, in_addr source_ip, short unsigned int source_port, in_addr destination_ip, short unsigned int destination_port,  const u_char* packet);

public slots:
    void run_button_click();
    void stop_button_click();
    void cellDoubleClick(int x, int y);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
