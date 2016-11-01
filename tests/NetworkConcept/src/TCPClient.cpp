#include "TCPClient.hpp"
#include <iostream>
#include <cstring>

TCPClient::TCPClient(const std::string &hostname, unsigned short port, QObject *parent) : hostName(hostname), port(port), QObject(parent)
{
  this->tcpSocket = new QTcpSocket(this);
  connect(this->tcpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
//  connect(this->tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error);
}

TCPClient::~TCPClient()
{

}

bool TCPClient::initiateService()
{
  this->tcpSocket->connectToHost(this->hostName.c_str(), this->port);
  return this->tcpSocket->waitForConnected();
}

bool TCPClient::sendBabelPacket(BabelPacket &packet)
{
  if(this->tcpSocket->state() == QAbstractSocket::ConnectedState)
  {
    std::cout << sizeof(BabelPacket) + packet.dataLength << std::endl;
    this->tcpSocket->write((const char *)&packet, sizeof(BabelPacket) + packet.dataLength);
    return this->tcpSocket->waitForBytesWritten();
  }
  else
    return false;
}


void TCPClient::shutDown()
{
  this->tcpSocket->abort();
}


void TCPClient::readMessage()
{
    char buffer[sizeof(BabelPacket)];
    this->tcpSocket->read(buffer, sizeof(BabelPacket));
    BabelPacket *packet = reinterpret_cast<BabelPacket *>(buffer);
    std::cout << packet->dataLength << std::endl;

    BabelPacket *fullPacket = reinterpret_cast<BabelPacket *>(
          new unsigned char[sizeof(BabelPacket) + packet->dataLength + 1]);
    std::memcpy(fullPacket, packet, sizeof(BabelPacket));
    char *packetData = new char[packet->dataLength + 1];
    this->tcpSocket->read(packetData, packet->dataLength);
    std::memcpy(fullPacket, packetData, packet->dataLength);
    //send to protocol
}
