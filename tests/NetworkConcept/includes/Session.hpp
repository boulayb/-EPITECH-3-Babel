#ifndef SESSION_HPP
#define SESSION_HPP

#include "Protocol.hpp"
#include <boost/bind.hpp>
#include <boost/asio.hpp>

class Session
{
public:
  Session(boost::asio::io_service& io_service);
  ~Session();
  void start();
  boost::asio::ip::tcp::socket &getSocket();
  int getUserId() const;
  void writeToClient(Protocol::BabelPacket const&);
private:
  void handleRead(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleReadData(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleWrite(const boost::system::error_code& error);
  void handleWrited(const boost::system::error_code &error, size_t bytes_transferred);
  boost::asio::ip::tcp::socket socket;
  unsigned char buffer[sizeof(Protocol::BabelPacket)];
  unsigned char *packetData;
  Protocol::BabelPacket *currentPacket;
  int userID;
};

#endif // SESSION_HPP
