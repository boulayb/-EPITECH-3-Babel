#include <iostream>
#include "Session.hpp"
#include "Server.hpp"

Session::Session(boost::asio::io_service &io_service) : socket(io_service), packetData(nullptr), currentPacket(nullptr), userID(-1), handShaked(false)
{

}

Session::~Session()
{
 if (this->currentPacket != nullptr)
   delete this->currentPacket;
 if (this->currentPacket != nullptr)
   delete this->packetData;
}

void Session::start(Server *server, unsigned int userId)
{
  this->server = server;
  this->userID = userId;
  std::string remoteHost = this->socket.remote_endpoint().address().to_string();
  Protocol::BabelPacket *packet = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::HAND_SHAKE,
                                                                   Protocol::Protocol::stringToPointer(remoteHost),
                                                                   remoteHost.size());
  this->writeToClient(*packet);
  this->socket.async_read_some(boost::asio::buffer(this->buffer, sizeof(Protocol::BabelPacket)),
      boost::bind(&Session::handleRead, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket &Session::getSocket()
{
  return this->socket;
}

unsigned int Session::getUserId() const
{
  return this->userID;
}

void Session::connectionLost()
{
  Protocol::BabelPacket *babelPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::INVALID_REQUEST,
                                                                        nullptr, 0);
  this->server->addTask(*babelPacket, this->userID);
}

void Session::handleReadData(const boost::system::error_code &error, size_t bytes_transferred)
{
  (void)bytes_transferred;
  if (error)
  {
    std::cerr << "Error happened during the packet transmission : " << error.message() <<std::endl;
    connectionLost();
    return;
  }
  else
  {
    std::memcpy(this->currentPacket->data, this->packetData, bytes_transferred);
    this->server->addTask(*this->currentPacket, this->userID);
    this->socket.async_read_some(boost::asio::buffer(this->buffer, sizeof(Protocol::BabelPacket)),
                                 boost::bind(&Session::handleRead, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
  }
}

void Session::handleRead(const boost::system::error_code &error, size_t bytes_transferred)
{
  if (error)
  {
    std::cerr << "Error happened during the packet transmission : " << error.message() <<std::endl;
    connectionLost();
    return;
  }
  Protocol::BabelPacket *packet;
  packet = reinterpret_cast<Protocol::BabelPacket *>(this->buffer);
  (void)bytes_transferred;
  this->currentPacket = reinterpret_cast<Protocol::BabelPacket *>(
        new unsigned char[sizeof(Protocol::BabelPacket) + packet->dataLength + 1]);
  std::memcpy(this->currentPacket, packet, sizeof(Protocol::BabelPacket));
  this->packetData = new unsigned char[this->currentPacket->dataLength + 1];
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
  (void)bytes_transferred;
  if (error)
  {
    std::cerr << "Error happened during the packet transmission : " << error.message() <<std::endl;
    connectionLost();
    return;
  }
}

void Session::writeToClient(const Protocol::BabelPacket &packet)
{
  this->socket.async_write_some(boost::asio::buffer(&packet, sizeof(Protocol::BabelPacket) + packet.dataLength),
                                boost::bind(&Session::handleWrited, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred
                                ));
}

const boost::asio::ip::tcp::socket& Session::getSocket() const
{
  return this->socket;
}
