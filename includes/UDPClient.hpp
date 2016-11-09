#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QUdpSocket>
#include <QDebug>
#include <QIODevice>
#include "ANetwork.hpp"
#include "client.hpp"

class UDPClient : public  QObject, public ANetwork
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
  QUdpSocket udpSocket;
};

#endif // UDPCLIENT_H
