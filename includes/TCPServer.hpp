#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <vector>
#include "Session.hpp"

class TCPServer
{
public:
  TCPServer(Server *, unsigned short port);
  ~TCPServer();
  bool initiateService();
  void shutDown();
  bool sendBabelPacket(Protocol::BabelPacket &, unsigned int);
  bool disconnectUser(unsigned int userID);
private:
  void handle_accept(Session* new_session,
      const boost::system::error_code& error);
  void startAccept();

  boost::asio::io_service ioService;
  boost::asio::ip::tcp::acceptor acceptor;
  std::vector<Session *> users;
  unsigned int maxUserId;
  Server *server;
};

#endif // TCPSERVER_HPP
