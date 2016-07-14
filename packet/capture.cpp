#include "mainwindow.h"
#include<iostream>
#include <pcap.h>
#include <arpa/inet.h>
using namespace std;

extern MainWindow *indexWindow;

void test(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    char source_mac[20], destination_mac[20];
    unsigned short ethernet_type;
    char ip_version;
    char protocol;
    long source_ip_long, destination_ip_long;
    unsigned short source_port, destination_port;

    //cout << ++packetCount << " packet(s) captured" << endl;

    sprintf(destination_mac, "%02x:%02x:%02x:%02x:%02x:%02x", \
            (void*)packet[0], (void*)packet[1], (void*)packet[2], \
            (void*)packet[3], (void*)packet[4], (void*)packet[5]);                     // get Destination MAC Address
    sprintf(source_mac, "%02x:%02x:%02x:%02x:%02x:%02x", \
            (void*)packet[6], (void*)packet[7], (void*)packet[8], \
            (void*)packet[9], (void*)packet[10], (void*)packet[11]);                   // get Sourc MAC Address

    ethernet_type = ntohs(*((unsigned short *)&(packet[12])));                         // get Ethernet Type

    if(ethernet_type == 0x0800){                                                       // ethernet_type == IP

        ip_version = packet[14] >> 4;
        if((int)ip_version == 4){                                                      // ip_version == 4
            protocol = packet[23];
            if((int)protocol == 6){                                                    // protocol == tcp
                source_ip_long = *((long *)&(packet[26]));                             // get Source IP
                destination_ip_long = *((long *)&(packet[30]));                        // get Destination IP
                struct in_addr source_ip;
                struct in_addr destination_ip;
                source_ip.s_addr = source_ip_long;
                destination_ip.s_addr = destination_ip_long;

                source_port = ntohs(*((unsigned short *)&(packet[34])));               // get Source Port
                destination_port = ntohs(*((unsigned short *)&(packet[36])));          // get Destination Port

                indexWindow -> on_packet_capture(pkthdr->len, source_mac, destination_mac, source_ip, source_port, destination_ip, destination_port, packet);

            }
        }

    }

}
