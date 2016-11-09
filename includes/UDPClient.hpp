#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QObject>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QUdpSocket>
#include <QDebug>
#include <QIODevice>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "INetwork.hpp"
#include "client.hpp"

class UDPClient : public  QObject, public INetwork
{
  Q_OBJECT

 public:
  UDPClient(Client *, std::string const &hostname, unsigned short port, QObject *parent = 0);
  ~UDPClient();
  bool initiateService();
  void shutDown();
  bool sendBabelPacket(Protocol::BabelPacket &);
private slots:
  void displayError(QAbstractSocket::SocketError socketError);
  void readMessage();
private:
  Client *babel;
  std::string hostName;
  short port;
  QUdpSocket udpSocket;
};

#endif // UDPCLIENT_H
