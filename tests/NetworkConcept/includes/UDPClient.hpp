#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QIODevice>
#include "INetwork.hpp"

class UDPClient : public  QObject, public INetwork
{
  Q_OBJECT
public:
  UDPClient(std::string const &hostname, unsigned short port, QObject *parent = 0);
  ~UDPClient();
  bool initiateService();
  void shutDown();
  bool sendBabelPacket(BabelPacket &);
private slots:
  void readMessage();
private:
  QString hostName;
  quint16 port;
  QUdpSocket *udpSocket;
};

#endif // UDPCLIENT_H
