#include <iostream>
#include <cstring>
#include "client.hpp"
#include "gui.hh"

Client::Client(Gui *gui) : gui(gui)
{
  this->tcpClient = new TCPClient(this, "127.0.0.1", 4001);
  this->tcpClient->initiateService();
}

Client::~Client()
{
}

void       Client::startGUI()
{
  this->gui->start();
}

void       Client::readBabelPacket(Protocol::BabelPacket const &packet)
{
  std::cout << (int)packet.code << " = code" << std::endl;
  (this->*(this->readFunctions[packet.code]))(packet);
}

void       Client::registerResponse(Protocol::BabelPacket const &packet)
{
  this->gui->setLoginView();
  this->gui->affInfoMessage("Register success");
}

void       Client::sendBabelPacket(Protocol::BabelPacket::Code const code, std::string const &user, std::string const &passwd)
{
  unsigned char *data = Protocol::Protocol::stringToPointer(user + ':' + passwd);
  unsigned int length = strlen(reinterpret_cast<char *>(data));
  Protocol::BabelPacket   *packet = Protocol::Protocol::createPacket(code, data, length);
  this->tcpClient->sendBabelPacket(*packet);
  std::cout << "packet send" << std::endl;
}

void       Client::handshake(Protocol::BabelPacket const &packet)
{
  Protocol::BabelPacket   *handshakeSuccess = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::HAND_SHAKE_SUCCESS, nullptr, 0);
  this->tcpClient->sendBabelPacket(*handshakeSuccess);
}

void       Client::login(Protocol::BabelPacket const &packet)
{
  std::cout << "login" << std::endl;
  this->gui->Login();
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  this->tcpClient->sendBabelPacket(*newPacket);
  std::cout << "packet send" << std::endl;
}

void       Client::logout(Protocol::BabelPacket const &packet)
{
  this->gui->setLoginView();
}

void       Client::updateContactList(Protocol::BabelPacket const &packet)
{
  std::vector<std::pair<std::string, bool>> contactList;
  std::string data(const_cast<char *>(reinterpret_cast<const char *>(packet.data)));
  std::string name = "";
  std::string status = "";

  std::cout << "Add list" << std::endl;
  while (data.size() > 1)
    {
      name = data.substr(0, data.find(":"));
      std::cout << "data: " << data << std::endl;
      data = data.substr(data.find(":") + 1);
      std::cout << "data: " << data << std::endl;
      status = data.substr(0, data.find(";"));
      data = data.substr(data.find(";"));
      std::cout << "data: " << data << std::endl;
      std::cout << "+1" << std::endl;
      if (status == "online")
	contactList.push_back(std::pair<std::string, bool>(name,true));
      else
	contactList.push_back(std::pair<std::string, bool>(name,false));
    }
  for (std::pair<std::string, bool> each: contactList)
    {
      std::cout << "name: " << each.first << ", status: " << each.second << std::endl;
    }
  this->gui->UpdateContactList(contactList);
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
      this->gui->UpdateContact(contactStatus);
    }
}

void       Client::incomingCall(Protocol::BabelPacket const &packet)
{
//  this->gui->
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
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  this->tcpClient->sendBabelPacket(*newPacket);
  std::cout << "packet send" << std::endl;
}

void       Client::contactDeleted(Protocol::BabelPacket const &packet)
{
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  this->tcpClient->sendBabelPacket(*newPacket);
  std::cout << "packet send" << std::endl;
}

void       Client::errorEncountered(Protocol::BabelPacket const &packet)
{
  if (packet.code == Protocol::BabelPacket::Code::USER_ALREADY_SIGNED_IN)
  {
    this->gui->affInfoMessage("User already signed in");
  }
  else if (packet.code == Protocol::BabelPacket::Code::USER_ALREADY_EXIST)
  {
    this->gui->affInfoMessage("User already exist");
  }
    //this->gui->errorEncountered(error);
}

