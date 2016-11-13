#ifndef TCPCLIENT_HHP
#define TCPCLIENT_HHP

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QObject>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QIODevice>
#include "ANetwork.hpp"

#ifdef _MSC_VER
#pragma warning(pop)
#endif

class Client;

class TCPClient : public  QObject, public ANetwork
{
  Q_OBJECT
public:
  TCPClient(Client *, std::string const &hostname, unsigned short port, QObject *parent = 0);
  ~TCPClient();
  bool initiateService();
  void shutDown();
  bool sendBabelPacket(Protocol::BabelPacket &);
  private:
private slots:
  void readMessage();
  void displayError(QAbstractSocket::SocketError socketError);
private:
  QTcpSocket tcpSocket;
};

#endif // TCPCLIENT_HHP
