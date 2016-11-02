#ifndef INETWORK_HPP
#define INETWORK_HPP

#include <string>
#include "Protocol.hpp"

class INetwork
{
public:
  virtual ~INetwork() {}
  virtual bool      initiateService() = 0;
  virtual void      shutDown() = 0;
  virtual bool      sendBabelPacket(BabelPacket &) = 0;
};

#endif // INETWORK_HPP
