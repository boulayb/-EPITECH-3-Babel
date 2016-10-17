#include <QtCore>
#include <QtNetwork>
#include "TCPClient.hpp"
#include "TCPServer.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
  Protocol::BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(new char[sizeof(Protocol::BabelPacket) + 5]);
  packet->senderId = 1;
  strcpy(packet->data, "kappa");
  packet->dataLength = 5;
  INetwork *socket = new TCPClient("127.0.0.1", 4000);
  socket->initiateService();
  socket->sendBabelPacket(*packet);
}

