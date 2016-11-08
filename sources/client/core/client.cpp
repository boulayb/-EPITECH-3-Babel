#include <iostream>
#include <cstring>
#include "client.hpp"

Client::Client()
{
}

Client::~Client()
{
}

void       Client::readBabelPacket(Protocol::BabelPacket const &packet)
{
  (this->*(this->readFunctions[packet.code]))(packet);
}

void       Client::sendBabelPacket(Protocol::BabelPacket::Code const code, std::string const &user, std::string const &passwd)
{
  unsigned char *data = Protocol::Protocol::stringToPointer(user + passwd);
  unsigned int length = strlen(reinterpret_cast<char *>(data));
  Protocol::BabelPacket   *packet = Protocol::Protocol::createPacket(code, data, length);
  this->tcpClient->sendBabelPacket(*packet);
}

void       Client::handshake(Protocol::BabelPacket const &packet)
{
  Protocol::BabelPacket   *handshakeSuccess = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::HAND_SHAKE_SUCCESS, nullptr, 0);
  this->tcpClient->sendBabelPacket(*handshakeSuccess);
}

void       Client::login(Protocol::BabelPacket const &packet)
{
  //this->gui->login();
}

void       Client::logout(Protocol::BabelPacket const &packet)
{
  //this->gui->logout();
}

void       Client::updateContactList(Protocol::BabelPacket const &packet)
{
  std::vector<std::pair<std::string, bool>> contactList;
  std::string data(const_cast<char *>(reinterpret_cast<const char *>(packet.data)));
  std::string name = "";
  std::string status = "";

  while ((name = data.substr(0, data.find(":"))) != "")
    {
      status = data.substr(0, data.find(";"));
      if (status == "1")
	contactList.push_back(std::pair<std::string, bool>(name,true));
      else
	contactList.push_back(std::pair<std::string, bool>(name,false));
    }
  //this->gui->updateContactList(contactList);
}

void       Client::updateContactStatus(Protocol::BabelPacket const &packet)
{
  std::pair<std::string, bool> contactStatus;
  std::string data(const_cast<char *>(reinterpret_cast<const char *>(packet.data)));
  std::string name = "";

  if ((name = data.substr(0, data.find(":"))) != "")
    {
      std::string status = data.substr(0, data.find(";"));
      if (status == "1")
	contactStatus = std::make_pair(name, true);
      else
	contactStatus = std::make_pair(name, false);
      //this->gui->updateContactStatus(contactStatus);
    }
}

void       Client::incomingCall(Protocol::BabelPacket const &packet)
{
  //this->gui->incomingCall();
}

void       Client::callAccepted(Protocol::BabelPacket const &packet)
{
  //this->gui->callAccepted();
}

void       Client::callDeclined(Protocol::BabelPacket const &packet)
{
  //this->gui->callDeclined();
}

void       Client::contactAdded(Protocol::BabelPacket const &packet)
{
  //this->gui->contactAdded();
}

void       Client::contactDeleted(Protocol::BabelPacket const &packet)
{
  //this->gui->contactDeleted();
}

void       Client::errorEncountered(Protocol::BabelPacket const &packet)
{
  std::string error(const_cast<char *>(reinterpret_cast<const char *>(packet.data)));
  //this->gui->errorEncountered(error);
}
