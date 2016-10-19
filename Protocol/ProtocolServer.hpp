#ifndef PROTOCOLSERVER_HPP_
# define PROTOCOLSERVER_HPP_

# include "AProtocol.hpp"

namespace Protocol
{
  class ProtocolServer: public AProtocol
  {
  public:
    ProtocolServer();
    virtual ~ProtocolServer();
    virtual void	readPacket(struct BabelPacket const & packet) const;
    virtual void	readSignUp(struct BabelPacket const & packet) const;
    virtual void	readSignIn(struct BabelPacket const & packet) const;
    virtual void	readContactList(struct BabelPacket const & packet) const;
    virtual void	readCall(struct BabelPacket const & packet) const;
    virtual void	readAddContact(struct BabelPacket const & packet) const;

    struct BabelPacket	sendSignUp();
    struct BabelPacket	sendSignIn();
    struct BabelPacket	readSignOut();
    struct BabelPacket	sendContactList();
    struct BabelPacket	sendCall();
    struct BabelPacket	sendAddContact();
    struct BabelPacket	readPing();
  };
}

#endif /* !PROTOCOLSERV_HPP_ */
