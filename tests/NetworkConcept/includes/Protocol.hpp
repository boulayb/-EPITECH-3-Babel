//
// Protocol.hpp for Babel_Protocol
//
// Made by Nicolas Zordan
// Login   <zordan_n@epitech.net>
//
// Started on  Sat Oct 15 15:46:54 2016 Nicolas Zordan
// Last update Thu Oct 27 16:26:31 2016 Victor Schuchmann
//

#ifndef BABEL_PROTOCOL_HPP_
# define BABEL_PROTOCOL_HPP_

# ifdef WIN32
#  pragma warning(disable : 4200)
# endif // WIN32

# define MAGIC_NUMBER   0xDEAD

struct		BabelPacket
{
  // Code enum
  enum Code : unsigned int
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
    INVALID_REQUEST = 001,
    USER_NOT_FOUND = 002,
    WRONG_PASSWORD = 003,
    USER_ALREADY_EXIST = 004,
    NOT_LOGGED_IN = 005,
    USER_DOES_NOT_EXIST = 006,
    DECLINE_CALL = 007,
    // Success
    LOGIN_SUCCESS = 200,
    SIGN_UP_SUCCESS = 201,
    DISCONNECT_SUCCESS = 202,
    CONTACT_LIST = 203,
    ACCEPT_CALL = 204,
    CONTACT_ADDED = 205,
  };

  // Infos
  unsigned int	magicNbr;
  unsigned int	date;

  // Data
  Code		code;
  unsigned int	dataLength;
  unsigned char	data[0];
};

#endif // !BABEL_PROTOCOL_HPP_
