#ifndef PROTOCOL_HPP_
# define PROTOCOL_HPP_

# define MAGIC_NUMBER   0xDEAD

namespace Protocol
{
  struct          BabelPacket
  {
    // Code enum
    enum class Code : unsigned int
      {
	NONE = 00,
	// Requests
	SIGN_IN = 100,
	SIGN_UP = 101,
	SIGN_OUT = 102,
	CONTACT_LIST_REQUEST = 103,
	CALL = 104,
	ADD_CONTACT = 105,
	DEL_CONTACT = 106,
	UPDATE_CONTACT_STATUS = 107,
	// Errors
	INVALID_REQUEST = 1,
	USER_NOT_FOUND = 2,
	WRONG_PASSWORD = 3,
	USER_ALREADY_EXIST = 4,
	NOT_LOGGED_IN = 5,
	USER_DOES_NOT_EXIST = 6,
	DECLINE_CALL = 7,
	ALREADY_A_FRIEND = 8,
	FRIEND_NOT_FOUND = 9,
	// Success
	LOGIN_SUCCESS = 200,
	SIGN_UP_SUCCESS = 201,
	DISCONNECT_SUCCESS = 202,
	CONTACT_LIST = 203,
	ACCEPT_CALL = 204,
	CONTACT_ADDED = 205,
	CONTACT_DELETED = 205,
	ID_ADDED = 206,
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
  };

}


#endif /* !PROTOCOL_HPP_ */
