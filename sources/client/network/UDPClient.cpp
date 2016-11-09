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
  this->udpSocket.bind();
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
  std::string data = Protocol::Protocol::extractData(packet);
  std::cout << sizeof(Protocol::BabelPacket) + packet.dataLength << std::endl;
  QHostAddress addr(qHostname);
  this->udpSocket.writeDatagram(data.c_str(), packet.dataLength, addr, this->port);
  return true;
}

void UDPClient::shutDown()
{
  this->udpSocket.abort();
}


void UDPClient::readMessage()
{
  QByteArray buffer;
  buffer.resize(this->udpSocket.pendingDatagramSize());
  QHostAddress sender;
  quint16 senderPort;

  this->udpSocket.readDatagram(buffer.data(), buffer.size(),
                       &sender, &senderPort);

  qDebug() << "Message from: " << sender.toString();
  qDebug() << "Message port: " << senderPort;
  qDebug() << "Message: " << buffer;
}
