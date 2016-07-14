#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <list>
#include <vector>
#include <iostream>
using namespace std;

class PacketdataList {
    vector<const u_char*> packetList;
  public:
    PacketdataList();
    void save_packet (const u_char* );
    const u_char* get_packet (int offset);
};

#endif // PACKETDATA_H
