#ifndef SESSION_HPP
#define SESSION_HPP

#include "Protocol.hpp"
#include <boost/bind.hpp>
#include <boost/asio.hpp>

class Session
{
public:
  Session(boost::asio::io_service& io_service);
  void start();
  boost::asio::ip::tcp::socket &getSocket();
private:
  void handleRead(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleReadData(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleWrite(const boost::system::error_code& error);

  boost::asio::ip::tcp::socket socket;
  char buffer[sizeof(Protocol::BabelPacket)];
  char *packetData;
  Protocol::BabelPacket *currentPacket;
};

#endif // SESSION_HPP
