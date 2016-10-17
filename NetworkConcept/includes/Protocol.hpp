#ifndef BABEL_PROTOCOL_HPP_
# define BABEL_PROTOCOL_HPP_

# define MAGIC_NUMBER   0xDEAD

namespace Protocol
{
  enum class      Request : int
  {
    ERROR = -1,
    CONNECT = 0,
    DISCONNECT,
    PING,
    PONG,
    CONTACT_LIST,
    UPDATE_CONTACT_STATUS,
    CALL,
    PICK_UP,
    HANG_UP,
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
    char          data[0];
  };
}

#endif // !BABEL_PROTOCOL_HPP_
