#include <iostream>
#include "UDPClient.hpp"


UDPClient::UDPClient(Client *client, const std::string &hostname, unsigned short port, QObject *parent) : QObject(parent), ANetwork(client, hostname, port)
{
  connect(&this->udpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
  connect(&this->udpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

UDPClient::~UDPClient()
{

}

bool UDPClient::initiateService()
{
  std::cout << "binding ! " << this->hostName << " "<< this->port << std::endl;
  this->udpSocket.bind(QHostAddress::Any, this->port, QUdpSocket::ReuseAddressHint);
  return true;
}

void UDPClient::displayError(QAbstractSocket::SocketError socketError)
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

bool UDPClient::sendBabelPacket(Protocol::BabelPacket &packet)
{
  QString qHostname(this->hostName.c_str());
//  std::string data = Protocol::Protocol::extractData(packet);
//  std::cout << sizeof(Protocol::BabelPacket) + packet.dataLength << std::endl;
  QHostAddress addr(qHostname);
  std::cout << "writing to " << this->hostName << " " << this->port << std::endl;
  this->udpSocket.writeDatagram((char *)&packet, sizeof(Protocol::BabelPacket) + packet.dataLength, addr, this->port);
  this->udpSocket.flush();
  return true;
}

void UDPClient::shutDown()
{
  this->udpSocket.abort();
}

void UDPClient::readMessage()
{
  while (this->udpSocket.hasPendingDatagrams())
  {
    std::cout << "READING PACKET UDP" << std::endl;
    QByteArray buffer;
    buffer.resize(this->udpSocket.pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    this->udpSocket.readDatagram(buffer.data(), buffer.size(),
                                 &sender, &senderPort);
    Protocol::BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(buffer.data());
    this->client->callPacket((char *)packet->data, packet->dataLength);
  }
}
