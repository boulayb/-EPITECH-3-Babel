#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include <map>
# include <vector>
# include <thread>
# include <chrono>
# include "INetwork.hpp"
# include "Protocol.hpp"
# include "TCPClient.hpp"
# include "UDPClient.hpp"
# include "PackBuilder.hh"

class Gui;

class Client
{
private:
  INetwork  *tcpClient;
  INetwork  *udpClient;
  Gui       *gui;
  PackBuilder   packBuilder;
  bool      inCall;
  std::thread udpThread;
  std::string hostname;
  short       udpPort;
  std::string callerName;

  typedef void (Client::*fptr)(Protocol::BabelPacket const &);
  std::map<Protocol::BabelPacket::Code, fptr>      readFunctions =
    {
      {Protocol::BabelPacket::Code::HAND_SHAKE, &Client::handshake},
      {Protocol::BabelPacket::Code::SIGN_IN_SUCCESS, &Client::login},
      {Protocol::BabelPacket::Code::SIGN_UP_SUCCESS, &Client::registerResponse},
      {Protocol::BabelPacket::Code::SIGN_OUT_SUCCESS, &Client::logout},
      {Protocol::BabelPacket::Code::CONTACT_LIST_SUCCESS, &Client::updateContactList},
      {Protocol::BabelPacket::Code::UPDATE_CONTACT_STATUS, &Client::updateContactStatus},
      {Protocol::BabelPacket::Code::CALL, &Client::incomingCall},
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
      {Protocol::BabelPacket::Code::AUDIO, &Client::callPacket},
      {Protocol::BabelPacket::Code::VIDEO, &Client::ignorPacket},
      {Protocol::BabelPacket::Code::TEXT, &Client::readText},
      {Protocol::BabelPacket::Code::HANG_UP, &Client::hangUp},
      {Protocol::BabelPacket::Code::USER_NOT_FRIEND, &Client::errorEncountered}
    };

  // Server HandShake request
  void       handshake(Protocol::BabelPacket const &packet);

  // Server Success Replies
  void       login(Protocol::BabelPacket const &packet);
  void       registerResponse(Protocol::BabelPacket const &packet);
  void       logout(Protocol::BabelPacket const &packet);
  void       updateContactList(Protocol::BabelPacket const &packet);
  void       updateContactStatus(Protocol::BabelPacket const &packet);
  void       incomingCall(Protocol::BabelPacket const &packet);
  void       callAccepted(Protocol::BabelPacket const &packet);
  void       callDeclined(Protocol::BabelPacket const &packet);
  void       contactAdded(Protocol::BabelPacket const &packet);
  void       contactDeleted(Protocol::BabelPacket const &packet);
  void       callPacket(Protocol::BabelPacket const &packet);
  void       hangUp(Protocol::BabelPacket const &packet);
  void       inCallThread();
  void       readText(Protocol::BabelPacket const &packet);

  // Server Error Replies
  void       errorEncountered(Protocol::BabelPacket const &packet);
  void       ignorPacket(Protocol::BabelPacket const &packet);
  std::thread spawn() {
    return std::thread( [this] { this->inCallThread(); } );
  }
 public:
  Client(Gui *);
  ~Client();
  void       startGUI();
  void       readBabelPacket(Protocol::BabelPacket const &packet);
  void       sendBabelPacket(Protocol::BabelPacket::Code const code, std::string const &data1 = "", std::string const &data2 = "");
  void       sendCallPacket(std::string const &user = "");
  void       acceptCall(std::string const &user, std::string const &ip, std::string const &port);
  void       endCall();
};

#endif /* !CLIENT_HPP_ */
