#ifndef INETWORK_HPP
#define INETWORK_HPP

#include "Protocol.hpp"

class INetwork
{
public:
  virtual ~INetwork() {}
  virtual bool      initiateService() = 0;
  virtual void      shutDown() = 0;
  virtual bool      sendBabelPacket(Protocol::BabelPacket &) = 0;
};

#endif // INETWORK_HPP
