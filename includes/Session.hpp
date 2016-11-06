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
  unsigned int getUserId() const;
  void writeToClient(Protocol::BabelPacket const&);
  //const boost::asio::ip::tcp::socket& getSocket() const;

  boost::asio::ip::tcp::socket socket;
private:
  void handleRead(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleReadData(const boost::system::error_code& error,
      size_t bytes_transferred);
  void handleWrite(const boost::system::error_code& error);
  void handleWrited(const boost::system::error_code &error, size_t bytes_transferred);


  //boost::asio::ip::tcp::socket socket;
  unsigned char buffer[sizeof(Protocol::BabelPacket)];
  unsigned char *packetData;
  Protocol::BabelPacket *currentPacket;
  unsigned int userID;
  Server *server;
};

#endif // SESSION_HPP
