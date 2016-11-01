#include "TCPServer.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
  INetwork *socket = new TCPServer(4001);
  socket->initiateService();
//  socket->sendBabelPacket(packet);
}

