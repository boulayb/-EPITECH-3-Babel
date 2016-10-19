#ifndef APROTOCOL_HPP_
# define APROTOCOL_HPP_

# define MAGIC_NUMBER   0xDEAD

namespace Protocol
{
  enum class      Request : int
  {
    ERROR = -1,
      SIGN_IN = 0,
      SIGN_UP,
      SIGN_OUT,
      PING,
      CONTACT_LIST,
      UPDATE_CONTACT_STATUS,
      CALL,
      ADD_CONTACT,
      DEL_CONTACT
      };

  enum class    ReturnValue : int
  {
    FAILURE = -1,
      NONE = 0,
      SUCCESS = 1
      };

  struct          __attribute__((packed)) BabelPacket
  {
    unsigned      magicNbr = MAGIC_NUMBER;
    unsigned      senderId;
    unsigned      receiverId;
    unsigned      date;
    ReturnValue   returnValue;
    Request       requestType;
    unsigned      dataLength;
    unsigned char data[0];
  };

  class AProtocol
  {
  public:
    AProtocol();
    virtual ~AProtocol();
    virtual void	readPacket(struct BabelPacket const & packet) const = 0;
    virtual void	readSignUp(struct BabelPacket const & packet) const = 0;
    virtual void	readSignIn(struct BabelPacket const & packet) const = 0;
    virtual void	readContactList(struct BabelPacket const & packet) const = 0;
    virtual void	readCall(struct BabelPacket const & packet) const = 0;
    virtual void	readAddContact(struct BabelPacket const & packet) const = 0;
  };
}

#endif /* !APROTOCOL_HPP_ */
