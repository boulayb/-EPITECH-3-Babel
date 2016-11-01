#include <QtCore>
#include <QtNetwork>
#include "TCPClient.hpp"
#include "TCPServer.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
  BabelPacket *packet = reinterpret_cast<BabelPacket *>(new char[sizeof(BabelPacket) + strlen(argv[1])]);
  memcpy(packet->data, argv[1], strlen(argv[1]));
  packet->dataLength = strlen(argv[1]);
  INetwork *socket = new TCPClient("127.0.0.1", 4001);
  socket->initiateService();
  socket->sendBabelPacket(*packet);
  sleep(10);
}

