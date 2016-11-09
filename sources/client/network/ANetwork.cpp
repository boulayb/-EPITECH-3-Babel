#include "ANetwork.hpp"

ANetwork::ANetwork(Client *client, std::string const &hostname, short port) : client(client), hostName(hostname), port(port)
{

}

ANetwork::ANetwork()
{

}

ANetwork::~ANetwork()
{

}

void      ANetwork::setHostname(std::string const & hostname)
{
  this->hostName = hostname;
}

void      ANetwork::setPort(short port)
{
  this->port = port;
}

void      ANetwork::setClient(Client *client)
{
  this->client = client;
}