#ifndef PROTOCOL_HPP_
# define PROTOCOL_HPP_

# define MAGIC_NUMBER   0xDEAD
# include <string>

namespace Protocol
{
  struct          BabelPacket
  {
    enum class	Code : unsigned int
    {
	// Requests
    	HAND_SHAKE = 100,
      SIGN_IN = 101,
      SIGN_UP = 102,
      SIGN_OUT = 103,
      CONTACT_LIST = 104,
      CALL = 105,
      ADD_CONTACT = 106,
      DEL_CONTACT = 107,
      UPDATE_CONTACT_STATUS = 108,
      PING = 109,
      HANG_UP = 110,
      // Errors
      INVALID_REQUEST = 1,
      USER_NOT_FOUND = 2,
      SIGN_IN_FAILED = 3,
      USER_ALREADY_SIGNED_IN = 4,
      USER_ALREADY_EXIST = 5,
      NOT_SIGNED_IN = 6,
      USER_ALREADY_FRIEND = 7,
      USER_NOT_FRIEND = 8,
      // Success
      HAND_SHAKE_SUCCESS = 200,
      SIGN_IN_SUCCESS = 201,
      SIGN_UP_SUCCESS = 202,
      SIGN_OUT_SUCCESS = 203,
      CONTACT_LIST_SUCCESS = 204,
      CALL_ACCEPTED = 205,
      CALL_DECLINED = 206,
      CONTACT_ADD_SUCCESS = 207,
      CONTACT_DEL_SUCCESS = 208,

      // Info type between clients
      AUDIO = 301,
      TEXT = 302,
      VIDEO = 303
    };

    // Infos
    unsigned int        magicNbr;
    unsigned int        date;

    // Data
    Code                code;
    unsigned int        dataLength;
    unsigned char       data[0];
  };

  class Protocol
  {
  public:
        static struct BabelPacket *createPacket(BabelPacket::Code code, unsigned char *data, unsigned int const &length);
        static unsigned char      *stringToPointer(std::string const &);
	static std::string        &extractData(BabelPacket const &packet);
  };

}


#endif /* !PROTOCOL_HPP_ */
