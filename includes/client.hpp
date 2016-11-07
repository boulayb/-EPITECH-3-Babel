#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include <map>
# include <vector>
# include "INetwork.hpp"
# include "Protocol.hpp"

class Client
{
private:
  INetwork  *tcpClient;
  //Gui       *gui;

  typedef void (Client::*fptr)(Protocol::BabelPacket const &);
  std::map<Protocol::BabelPacket::Code, fptr>      readFunctions =
    {
      {Protocol::BabelPacket::Code::HAND_SHAKE, &Client::handshake},
      {Protocol::BabelPacket::Code::SIGN_IN_SUCCESS, &Client::login},
      {Protocol::BabelPacket::Code::SIGN_UP_SUCCESS, &Client::login},
      {Protocol::BabelPacket::Code::SIGN_OUT_SUCCESS, &Client::logout},
      {Protocol::BabelPacket::Code::CONTACT_LIST_SUCCESS, &Client::updateContactList},
      {Protocol::BabelPacket::Code::CALL_ACCEPTED, &Client::callAccepted},
      {Protocol::BabelPacket::Code::CALL_DECLINED, &Client::callDeclined},
      {Protocol::BabelPacket::Code::CONTACT_ADD_SUCCESS, &Client::contactAdded},
      {Protocol::BabelPacket::Code::CONTACT_DEL_SUCCESS, &Client::contactDeleted},
      {Protocol::BabelPacket::Code::INVALID_REQUEST, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::USER_NOT_FOUND, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::SIGN_IN_FAILED, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::USER_ALREADY_EXIST, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::USER_ALREADY_SIGNED_IN, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::NOT_SIGNED_IN, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::USER_ALREADY_FRIEND, &Client::errorEncountered},
      {Protocol::BabelPacket::Code::USER_NOT_FRIEND, &Client::errorEncountered}
    };

  // Server HandShake request
  void       handshake(Protocol::BabelPacket const &packet);

  // Server Success Replies
  void       login(Protocol::BabelPacket const &packet);
  void       logout(Protocol::BabelPacket const &packet);
  void       updateContactList(Protocol::BabelPacket const &packet);
  void       callAccepted(Protocol::BabelPacket const &packet);
  void       callDeclined(Protocol::BabelPacket const &packet);
  void       contactAdded(Protocol::BabelPacket const &packet);
  void       contactDeleted(Protocol::BabelPacket const &packet);

  // Server Error Replies
  void       errorEncountered(Protocol::BabelPacket const &packet);

 public:
  Client();
  ~Client();
  void       readBabelPacket(Protocol::BabelPacket const &packet);
  void       sendBabelPacket(Protocol::BabelPacket::Code const code, std::string const &user = "", std::string const &passwd = "");
};

#endif /* !CLIENT_HPP_ */
