#include "capturethread.h"
#include<iostream>
#include <pcap.h>
#include <arpa/inet.h>
#include <QMainWindow>
using namespace std;

CaptureThread::CaptureThread(QObject *parent):QThread(parent)
{

}

void CaptureThread::run()

{
    char *dev;
    pcap_t *descr;
    char errbuf[PCAP_ERRBUF_SIZE];

    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        cout << "pcap_lookupdev() failed: " << errbuf << endl;
        // exit
    }

    descr = pcap_open_live(dev, BUFSIZ, 0, -1, errbuf);
    if (descr == NULL) {
        cout << "pcap_open_live() failed: " << errbuf << endl;
        // exit
    }
    if (pcap_loop(descr, 0, test, NULL) < 0) {
        cout << "pcap_loop() failed: " << pcap_geterr(descr);
        // exit
    }
}






