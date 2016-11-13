#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QApplication>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <iostream>
#include <cstring>
#include "TCPClient.hpp"
#include "client.hpp"

TCPClient::TCPClient(Client *babel , const std::string &hostname, unsigned short port, QObject *parent) :
        QObject(parent), ANetwork(babel, hostname, port)
{
}

TCPClient::~TCPClient()
{

}

bool TCPClient::initiateService()
{
  connect(&this->tcpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
  connect(&this->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
  this->tcpSocket.connectToHost(this->hostName.c_str(), this->port);
  return this->tcpSocket.waitForConnected(5000);
}

bool TCPClient::sendBabelPacket(Protocol::BabelPacket &packet)
{
  if(this->tcpSocket.state() == QAbstractSocket::ConnectedState)
  {
    std::cout << "writing ... size : " << sizeof(Protocol::BabelPacket) + packet.dataLength<<std::endl;
    this->tcpSocket.write((const char *)&packet, sizeof(Protocol::BabelPacket) + packet.dataLength);
 //   this->tcpSocket.flush();
    return true;
  }
  else
  {
    return false;
  }
}


void TCPClient::shutDown()
{
  this->tcpSocket.abort();
}

void TCPClient::displayError(QAbstractSocket::SocketError socketError)
{
  std::cout << "wtf" << std::endl;
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
      std::cout << "1" << std::endl;
        break;
    case QAbstractSocket::HostNotFoundError:
      std::cout << "2" << std::endl;
      break;
    case QAbstractSocket::ConnectionRefusedError:
      std::cout << "3" << std::endl;

      break;
    default:
      std::cout << "4" << std::endl;
    }
}

void TCPClient::readMessage()
{

  std::cout << "read message tcp server" << std::endl;
  char buffer[sizeof(Protocol::BabelPacket)];
  qint64 ret;
  while ((ret = this->tcpSocket.read(buffer, sizeof(Protocol::BabelPacket))) > 0)
  {
    Protocol::BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(buffer);
    std::cout << "Receiving packet of size" << packet->dataLength << " with code " << (int) packet->code << std::endl;

    Protocol::BabelPacket *fullPacket = reinterpret_cast<Protocol::BabelPacket *>(
            new unsigned char[sizeof(Protocol::BabelPacket) + packet->dataLength + 1]);
    std::memcpy(fullPacket, packet, sizeof(Protocol::BabelPacket));
    char *packetData = new char[packet->dataLength];
    this->tcpSocket.read(packetData, packet->dataLength);
    std::memcpy(fullPacket->data, packetData, packet->dataLength);
    fullPacket->data[static_cast<int>(packet->dataLength)] = '\0';
    client->readBabelPacket(*fullPacket);
    buffer[0] = '\0';
  }
}
