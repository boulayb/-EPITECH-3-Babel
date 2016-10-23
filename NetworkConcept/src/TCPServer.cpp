#include "TCPServer.hpp"

TCPServer::TCPServer(unsigned short port): acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

TCPServer::~TCPServer()
{

}

bool TCPServer::initiateService()
{
  this->startAccept();
  return this->ioService.run();
}

void TCPServer::shutDown()
{

}

bool TCPServer::sendBabelPacket(Protocol::BabelPacket &packet)
{
  for (Session *user : this->users)
  {
    if (user->getUserId() == packet.receiverId)
    {
      user->writeToClient(packet);
    }
  }
  return (true);
}


void TCPServer::handle_accept(Session *newSession, const boost::system::error_code &error)
{
  if (!error)
  {
    newSession->start();
    this->users.push_back(newSession);
  }
  else
  {
    delete newSession;
  }
  this->startAccept();
}

void TCPServer::startAccept()
{
  Session* newSession = new Session(this->ioService);
  this->acceptor.async_accept(newSession->getSocket(),
      boost::bind(&TCPServer::handle_accept, this, newSession,
        boost::asio::placeholders::error));
}
