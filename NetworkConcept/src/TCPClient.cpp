#include "TCPClient.hpp"


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

#include <iostream>

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

Protocol::BabelPacket *TCPClient::getBabelPacket()
{

}

void TCPClient::shutDown()
{
  this->tcpSocket->abort();
}


void TCPClient::readMessage()
{
  while (!this->tcpSocket->atEnd()) {
      QByteArray data = this->tcpSocket->read(100);
  }
}
