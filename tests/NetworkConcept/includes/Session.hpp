#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Protocol.hpp"

class Server;

class Session
{
public:
  Session(boost::asio::io_service& io_service);
  ~Session();
  void start(Server *, unsigned int);
  boost::asio::ip::tcp::socket &getSocket();
  int getUserId() const;
  void writeToClient(BabelPacket const&);
private:
  void handleRead(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleReadData(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleWrite(const boost::system::error_code& error);
  void handleWrited(const boost::system::error_code &error, size_t bytes_transferred);


  boost::asio::ip::tcp::socket socket;
  unsigned char buffer[sizeof(BabelPacket)];
  unsigned char *packetData;
  BabelPacket *currentPacket;
  unsigned int userID;
  Server *server;
};

#endif // SESSION_HPP
