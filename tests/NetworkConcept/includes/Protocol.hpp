#ifndef BABEL_PROTOCOL_HPP_
# define BABEL_PROTOCOL_HPP_

#include <string>

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
    unsigned char          data[0];
  };

  class      PacketUtils
  {
  public:
    static std::string *extractData(BabelPacket const &packet)
    {
      unsigned size = packet.dataLength;
      std::string *data = new std::string;
      for (unsigned i = 0; i < size; ++i)
      {
        data += packet.data[i];
      }
      return data;
    }
  };
}

#endif // !BABEL_PROTOCOL_HPP_
