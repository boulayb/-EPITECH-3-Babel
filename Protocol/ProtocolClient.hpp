#ifndef PROTOCOLCLIENT_HPP_
# define PROTOCOLCLIENT_HPP_

# include "AProtocol.hpp"

namespace Protocol
{
  class ProtocolClient: public AProtocol
  {
  public:
    ProtocolClient();
    virtual ~ProtocolClient();
    virtual void	readPacket(struct BabelPacket const & packet) const;
    virtual void	readSignUp(struct BabelPacket const & packet) const;
    virtual void	readSignIn(struct BabelPacket const & packet) const;
    virtual void	readContactList(struct BabelPacket const & packet) const;
    virtual void	readCall(struct BabelPacket const & packet) const;
    virtual void	readAddContact(struct BabelPacket const & packet) const;

    struct BabelPacket	sendSignUp(std::string const & user, std::string const & password);
    struct BabelPacket	sendSignIn(std::string const & user, std::string const & password);
    struct BabelPacket	sendSignOut();
    struct BabelPacket	sendContactList();
    struct BabelPacket	sendCall(std::string const & name);
    struct BabelPacket	sendAddContact(std::string const & name);
    struct BabelPacket	sendPing();
  };
}


#endif /* !PROTOCOLCLIENT_HPP_ */
