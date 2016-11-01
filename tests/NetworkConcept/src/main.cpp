#include <QtCore>
#include <QtNetwork>
#include "TCPClient.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
  BabelPacket *packet = reinterpret_cast<BabelPacket *>(new char[sizeof(BabelPacket) + 5]);
  memcpy(packet->data, "kappa", 6);
  packet->dataLength = 5;
  INetwork *socket = new TCPClient("127.0.0.1", 4000);
  socket->initiateService();
  socket->sendBabelPacket(*packet);
}

