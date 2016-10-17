#include "TCPServer.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
  Protocol::BabelPacket packet;
  packet.senderId = 1;
  packet.date = 99;
  packet.dataLength = 0;
  INetwork *socket = new TCPServer(4000);
  socket->initiateService();
//  socket->sendBabelPacket(packet);
}

