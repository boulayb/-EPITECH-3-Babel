
#ifndef CPP_BABEL_ANETWORK_HPP
#define CPP_BABEL_ANETWORK_HPP

#include "INetwork.hpp"

class ANetwork : public INetwork
{
public:
  ANetwork(Client *, std::string const &, short);
  ANetwork();
  ~ANetwork();
  virtual bool                 initiateService() = 0;
  virtual void                 shutDown() = 0;
  virtual bool                 sendBabelPacket(Protocol::BabelPacket &) = 0;
  virtual void                 setHostname(std::string const &);
  virtual void                 setPort(short);
  virtual std::string const&   getHostname() const;
  virtual short const&         getPort() const;
  virtual void                 setClient(Client *);

protected:
  Client *client;
  std::string hostName;
  short port;
};

#endif //CPP_BABEL_ANETWORK_HPP
