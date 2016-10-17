#include "Session.hpp"
#include <iostream>

Session::Session(boost::asio::io_service &io_service) : socket(io_service)
{

}

void Session::start()
{
  socket.async_read_some(boost::asio::buffer(buffer, sizeof(Protocol::BabelPacket)),
      boost::bind(&Session::handleRead, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket &Session::getSocket()
{
  return this->socket;
}

void Session::handleReadData(const boost::system::error_code &error, size_t bytes_transferred)
{
  std::cout << bytes_transferred << std::endl;
  buffer[bytes_transferred] = 0;
  memcpy(this->currentPacket->data, packetData, bytes_transferred);
//  strcpy(this->currentPacket->data, packetData);
}

void Session::handleRead(const boost::system::error_code &error, size_t bytes_transferred)
{
  Protocol::BabelPacket *packet;
  packet = reinterpret_cast<Protocol::BabelPacket *>(buffer);
  std::cout << packet->senderId << std::endl;
  std::cout << packet->dataLength << std::endl;
  packetData = new char[packet->dataLength];
  socket.async_read_some(boost::asio::buffer(packetData, packet->dataLength),
      boost::bind(&Session::handleReadData, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Session::handleWrite(const boost::system::error_code &error)
{
  if (!error)
  {
    socket.async_read_some(boost::asio::buffer(buffer, sizeof(Protocol::BabelPacket)),
        boost::bind(&Session::handleRead, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
  else
  {
    delete this;
  }
}
