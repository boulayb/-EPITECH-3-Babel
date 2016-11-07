#include <iostream>
#include <cstring>
#include "TCPClient.hpp"

TCPClient::TCPClient(const std::string &hostname, unsigned short port, QObject *parent) : hostName(hostname), port(port), QObject(parent)
{
  this->tcpSocket = new QTcpSocket(this);
  connect(this->tcpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(displayError(QAbstractSocket::SocketError)));
}

TCPClient::~TCPClient()
{

}

bool TCPClient::initiateService()
{
  this->tcpSocket->connectToHost(this->hostName.c_str(), this->port);
  return this->tcpSocket->waitForConnected();
}

bool TCPClient::sendBabelPacket(Protocol::BabelPacket &packet)
{
  if(this->tcpSocket->state() == QAbstractSocket::ConnectedState)
  {
    std::cout << sizeof(Protocol::BabelPacket) + packet.dataLength << std::endl;
    this->tcpSocket->write((const char *)&packet, sizeof(Protocol::BabelPacket) + packet.dataLength);
    return this->tcpSocket->waitForBytesWritten();
  }
  else
    return false;
}


void TCPClient::shutDown()
{
  this->tcpSocket->abort();
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
  std::cout << "nice" << std::endl;
  char buffer[sizeof(Protocol::BabelPacket)];
  this->tcpSocket->read(buffer, sizeof(Protocol::BabelPacket));
  Protocol::BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(buffer);
  std::cout << "Receiving packet of size" << packet->dataLength << " " << (int)packet->code <<std::endl;

  Protocol::BabelPacket *fullPacket = reinterpret_cast<Protocol::BabelPacket *>(
        new unsigned char[sizeof(Protocol::BabelPacket) + packet->dataLength + 1]);
  std::memcpy(fullPacket, packet, sizeof(Protocol::BabelPacket));
  char *packetData = new char[packet->dataLength + 1];
  this->tcpSocket->read(packetData, packet->dataLength);
  std::memcpy(fullPacket, packetData, packet->dataLength);
  //send to protocol
}
