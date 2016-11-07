#include <iostream>
#include "UDPClient.hpp"


UDPClient::UDPClient(const std::string &hostname, unsigned short port, QObject *parent) : hostName(hostname.c_str()), port(port), QObject(parent)
{
  this->udpSocket = new QUdpSocket(this);
  connect(this->udpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
//  connect(this->udpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error);
}

UDPClient::~UDPClient()
{

}

bool UDPClient::initiateService()
{
  this->udpSocket->bind();
  return true;
}

bool UDPClient::sendBabelPacket(Protocol::BabelPacket &packet)
{
  std::string *data = Protocol::extractData(packet);
  std::cout << sizeof(Protocol::BabelPacket) + packet.dataLength << std::endl;
  QHostAddress addr(this->hostName);
  this->udpSocket->writeDatagram(data->c_str(), packet.dataLength, addr, this->port);
  return true;
}

void UDPClient::shutDown()
{
  this->udpSocket->abort();
}


void UDPClient::readMessage()
{
  QByteArray buffer;
  buffer.resize(this->udpSocket->pendingDatagramSize());
  QHostAddress sender;
  quint16 senderPort;

  this->udpSocket->readDatagram(buffer.data(), buffer.size(),
                       &sender, &senderPort);

  qDebug() << "Message from: " << sender.toString();
  qDebug() << "Message port: " << senderPort;
  qDebug() << "Message: " << buffer;
}
