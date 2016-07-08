#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <pcap.h>
#include <arpa/inet.h>
#include <QThread>


class CaptureThread : public QThread
{
    Q_OBJECT
public:
    CaptureThread(QObject *parent = 0);

private:
    void run();
    void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
};

void test(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
#endif // CAPTURETHREAD_H
