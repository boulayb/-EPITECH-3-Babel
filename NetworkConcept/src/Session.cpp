#include "Session.hpp"
#include "PacketFormater.hpp"
#include <iostream>

Session::Session(boost::asio::io_service &io_service) : socket(io_service), packetData(nullptr), currentPacket(nullptr), userID(-1)
{

}

Session::~Session()
{
 if (this->currentPacket != nullptr)
   delete this->currentPacket;
 if (this->currentPacket != nullptr)
   delete this->packetData;
}

void Session::start()
{
  socket.async_read_some(boost::asio::buffer(this->buffer, sizeof(Protocol::BabelPacket)),
      boost::bind(&Session::handleRead, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket &Session::getSocket()
{
  return this->socket;
}

int Session::getUserId() const
{
  return this->userID;
}

void Session::handleReadData(const boost::system::error_code &error, size_t bytes_transferred)
{
  std::cout << bytes_transferred << std::endl;
  for (int i = 0; this->packetData[i] != '\0' ; ++i)
  {
    std::cout << this->packetData[i] << std::endl;
  }
  std::memcpy(this->currentPacket->data, this->packetData, bytes_transferred);
  // packet ready, send to protocol here
}

void Session::handleRead(const boost::system::error_code &error, size_t bytes_transferred)
{
  Protocol::BabelPacket *packet;
  packet = reinterpret_cast<Protocol::BabelPacket *>(this->buffer);
  std::cout << packet->senderId << std::endl;
  std::cout << packet->dataLength << std::endl;
  this->userID = packet->senderId;
  this->currentPacket = reinterpret_cast<Protocol::BabelPacket *>(
        new unsigned char[sizeof(Protocol::BabelPacket) + packet->dataLength + 1]);
  std::memcpy(this->currentPacket, packet, sizeof(Protocol::BabelPacket));
  this->packetData = new unsigned char[packet->dataLength + 2];
  this->currentPacket = packet;
  this->socket.async_read_some(boost::asio::buffer(this->packetData, packet->dataLength),
                               boost::bind(&Session::handleReadData, this,
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred));
}

void Session::handleWrite(const boost::system::error_code &error)
{
  if (!error)
  {
    this->socket.async_read_some(boost::asio::buffer(this->buffer, sizeof(Protocol::BabelPacket)),
                                 boost::bind(&Session::handleRead, this,
                                 boost::asio::placeholders::error,
                                 boost::asio::placeholders::bytes_transferred
                                ));
  }
  else
  {
    delete this;
  }
}

void Session::handleWrited(const boost::system::error_code &error, size_t bytes_transferred)
{

}

void Session::writeToClient(const Protocol::BabelPacket &packet)
{
  this->socket.async_write_some(boost::asio::buffer(&packet, sizeof(Protocol::BabelPacket) + packet.dataLength),
                                boost::bind(&Session::handleWrited, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred
                                ));
}
