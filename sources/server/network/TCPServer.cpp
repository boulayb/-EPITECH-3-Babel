#include "TCPServer.hpp"
#include "Server.hpp"

TCPServer::TCPServer(Server *babelServer, unsigned short port):
  acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
  maxUserId(0),
  server(babelServer)
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

bool TCPServer::sendBabelPacket(Protocol::BabelPacket &packet, unsigned int id)
{
  for (Session *user : this->users)
  {
    if (user->getUserId() == id)
    {
      user->writeToClient(packet);
      return true;
    }
  }
  return false;
}

void TCPServer::handle_accept(Session *newSession, const boost::system::error_code &error)
{
  if (!error)
  {
    std::cout << "Accepting new user ! " << std::endl;
    newSession->start(server, this->maxUserId++);
    this->users.push_back(newSession);
  }
  else
  {
    delete newSession;
  }
  this->startAccept();
}

std::string TCPServer::getIpById(unsigned int id) const
{
  for (Session *user : this->users)
  {
    if (user->getUserId() == id)
    {
      return user->getSocket().remote_endpoint().address().to_string();
    }
  }
  return std::string("");
}

void TCPServer::startAccept()
{
  Session* newSession = new Session(this->ioService);
  this->acceptor.async_accept(newSession->getSocket(),
      boost::bind(&TCPServer::handle_accept, this, newSession,
        boost::asio::placeholders::error));
}
