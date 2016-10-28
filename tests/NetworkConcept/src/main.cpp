#include <QtCore>
#include <QtNetwork>
#include "TCPClient.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
  Protocol::BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(new char[sizeof(Protocol::BabelPacket) + 5]);
  packet->senderId = 1;
  memcpy(packet->data, "kappa", 6);
  packet->dataLength = 5;
  INetwork *socket = new TCPClient("127.0.0.1", 4000);
  socket->initiateService();
  socket->sendBabelPacket(*packet);
}

