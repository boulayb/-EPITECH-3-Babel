#include <iostream>
#include <cstring>
#include "TCPClient.hpp"
#include "client.hpp"
#include <QApplication>

TCPClient::TCPClient(Client *babel , const std::string &hostname, unsigned short port, QObject *parent) :
        QObject(parent), ANetwork(babel, hostname, port), is_connected(false)
{
}

TCPClient::~TCPClient()
{

}

bool TCPClient::initiateService()
{
  connect(&this->tcpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
  connect(&this->tcpSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(writeMessage(qint64)));
  connect(&this->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
  connect(&this->tcpSocket, SIGNAL(connected()), this, SLOT(connectReady()));
  connect(&this->tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectedReady()));
  this->tcpSocket.connectToHost(this->hostName.c_str(), this->port);
  return this->tcpSocket.waitForConnected(5000);
}

void TCPClient::connectReady()
{
  this->is_connected = true;
}

void TCPClient::writeMessage(qint64 bytes)
{
  (void)bytes;
  std::cout << "writted ! " << std::endl;
}

void TCPClient::disconnectedReady()
{

}


bool TCPClient::sendBabelPacket(Protocol::BabelPacket &packet)
{
  if(this->tcpSocket.state() == QAbstractSocket::ConnectedState && is_connected)
  {
    std::cout << "writing ... size : " << sizeof(Protocol::BabelPacket) + packet.dataLength<<std::endl;
    int ret = this->tcpSocket.write((const char *)&packet, sizeof(Protocol::BabelPacket) + packet.dataLength);
    std::cout << ret << std::endl;
    this->tcpSocket.flush();
    QApplication::processEvents();
    return true;
  }
  else
  {
    std::cout << "socket close" << std::endl;
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
  this->tcpSocket.read(buffer, sizeof(Protocol::BabelPacket));
  Protocol::BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(buffer);
  std::cout << "Receiving packet of size" << packet->dataLength << " with code " << (int) packet->code << std::endl;

  Protocol::BabelPacket *fullPacket = reinterpret_cast<Protocol::BabelPacket *>(
          new unsigned char[sizeof(Protocol::BabelPacket) + packet->dataLength]);
  std::memcpy(fullPacket, packet, sizeof(Protocol::BabelPacket));
  char *packetData = new char[packet->dataLength];
  this->tcpSocket.read(packetData, packet->dataLength);
  std::memcpy(fullPacket->data, packetData, packet->dataLength);
  fullPacket->data[static_cast<int>(packet->dataLength)] = '\0';
  client->readBabelPacket(*fullPacket);
  std::cout << this->tcpSocket.isOpen() << std::endl;
  //send to protocol
}
