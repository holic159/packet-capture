#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

int test();
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);

#endif // MAINWINDOW_H
