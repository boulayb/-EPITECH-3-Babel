#ifndef INETWORK_HPP
#define INETWORK_HPP

#include "Protocol.hpp"

class Client;

class INetwork
{
public:
  virtual ~INetwork() {}
  virtual bool                 initiateService() = 0;
  virtual void                 shutDown() = 0;
  virtual bool                 sendBabelPacket(Protocol::BabelPacket &) = 0;
  virtual void                 setHostname(std::string const &) = 0;
  virtual void                 setPort(short) = 0;
  virtual void                 setClient(Client *) = 0;
  virtual std::string const&   getHostname() const = 0;
  virtual short const&         getPort() const = 0;
};

#endif // INETWORK_HPP
