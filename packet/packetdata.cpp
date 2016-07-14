#include "packetdata.h"
#include <iostream>

using namespace std;

PacketdataList::PacketdataList(){

}

void PacketdataList::save_packet (const u_char* packet) {
  packetList.push_back(packet);
}

void PacketdataList::get_packet (int offset) {
  const u_char* temp_data;
  temp_data = packetList[0];
  cout << temp_data[1] << endl;
}
