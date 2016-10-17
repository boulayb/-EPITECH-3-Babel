#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include "Session.hpp"
#include "INetwork.hpp"

class TCPServer : public INetwork
{
public:
  TCPServer(unsigned short port);
  ~TCPServer();
  bool initiateService();
  void shutDown();
  bool sendBabelPacket(Protocol::BabelPacket &);
  Protocol::BabelPacket *getBabelPacket();
private:
  void handle_accept(Session* new_session,
      const boost::system::error_code& error);
  void startAccept();
  boost::asio::io_service ioService;
  boost::asio::ip::tcp::acceptor acceptor;
};

#endif // TCPSERVER_HPP
