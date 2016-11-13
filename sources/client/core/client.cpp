#include <iostream>
#include <cstring>
#include "client.hpp"
#include "gui.hh"

Client::Client(Gui *gui) : gui(gui), inCall(false)
{
  std::pair <std::string, int> netWorkInfo = this->gui->getNetworkInfo();
  this->tcpClient = new TCPClient(this, netWorkInfo.first, netWorkInfo.second);
  this->tcpClient->initiateService();
  this->udpClient = new UDPClient(this, "127.0.0.1", 4004);
  this->hostname = "127.0.0.1";
  this->udpPort = 4004;
//  this->udpClient->initiateService();
}

Client::~Client()
{
  this->inCall = false;
}

void       Client::startGUI()
{
  this->gui->start();
}

void       Client::readBabelPacket(Protocol::BabelPacket const &packet)
{
//  std::cout << (int)packet.code << " = code" << std::endl;
  (this->*(this->readFunctions[packet.code]))(packet);
}

void       Client::registerResponse(Protocol::BabelPacket const &packet)
{
  (void)packet;
  this->gui->setLoginView();
  this->gui->affInfoMessage("Register success");
}

void       Client::sendBabelPacket(Protocol::BabelPacket::Code const code, std::string const &user, std::string const &passwd)
{
  if (code == Protocol::BabelPacket::Code::CALL)
    {
      return Client::sendCallPacket(user);
    }

  unsigned char *data;
  std::string completeString = user + ':' + passwd;
  unsigned long size = 0;
  if (user != "")
    {
      if (passwd != "")
      {
        data = Protocol::Protocol::stringToPointer(completeString);
        size = completeString.length();
      }
      else
      {
        data = Protocol::Protocol::stringToPointer(user);
        size = user.length();
      }
    }
  Protocol::BabelPacket   *packet = Protocol::Protocol::createPacket(code, data, size);
  if (this->tcpClient->sendBabelPacket(*packet) == false)
    this->gui->affInfoMessage("Server is not responding ...");
  std::cout << "packet send" << std::endl;
}

void       Client::sendCallPacket(std::string const &user)
{
  std::string callData = user + ":" + this->hostname + ":" + std::to_string(this->udpPort);
  unsigned char *data = Protocol::Protocol::stringToPointer(callData);
  unsigned int length = strlen(reinterpret_cast<char *>(data));
  Protocol::BabelPacket   *packet = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CALL, data, length);
  if (this->tcpClient->sendBabelPacket(*packet) == false)
    this->gui->affInfoMessage("Server is not responding ...");
  std::cout << "packet send" << std::endl;
}

void       Client::handshake(Protocol::BabelPacket const &packet)
{
  std::string &hostName = Protocol::Protocol::extractData(packet);
  this->udpClient->setHostname(hostName);
  this->hostname = hostName;
  std::cout << "setting hostname " << hostName <<std::endl;

  Protocol::BabelPacket   *handshakeSuccess = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::HAND_SHAKE_SUCCESS, nullptr, 0);
  if (this->tcpClient->sendBabelPacket(*handshakeSuccess) == false)
    this->gui->affInfoMessage("Server is not responding ...");
}

void       Client::login(Protocol::BabelPacket const &packet)
{
  (void)packet;
  std::cout << "login" << std::endl;
  this->gui->Login();
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  if (this->tcpClient->sendBabelPacket(*newPacket) == false)
    this->gui->affInfoMessage("Server is not responding ...");
  std::cout << "packet send" << std::endl;
}

void       Client::logout(Protocol::BabelPacket const &packet)
{
  (void)packet;
  this->inCall = false;
  this->gui->setLoginView();
}

void       Client::updateContactList(Protocol::BabelPacket const &packet)
{
  std::vector<std::pair<std::string, bool>> contactList;
  std::string data(const_cast<char *>(reinterpret_cast<const char *>(packet.data)));
  std::string name = "";
  std::string status = "";
  std::string save;

  save = data;
  while (data.size() > 1)
    {
      name = data.substr(0, data.find(":"));
      data = data.substr(data.find(":") + 1);
      status = data.substr(0, data.find(";"));
      data = data.substr(data.find(";") + 1);
      if (status == "online")
        contactList.push_back(std::pair<std::string, bool>(name,true));
      else
        contactList.push_back(std::pair<std::string, bool>(name,false));
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
      std::cout << "DATA : " << data << std::endl;
      data = data.substr(data.find(":") + 1);
      std::cout << "STATUS : " << data << std::endl;
      if (data == "online")
        contactStatus = std::make_pair(name, true);
      else
        contactStatus = std::make_pair(name, false);
      this->gui->UpdateContact(contactStatus);
    }
}

void       Client::incomingCall(Protocol::BabelPacket const &packet)
{
  std::string data = Protocol::Protocol::extractData(packet);
  std::string user = data.substr(0, data.find(":"));
  data = data.substr(data.find(":") + 1);
  std::string ip = data.substr(0, data.find(":"));
  std::string port = data.substr(data.find(":") + 1);
  std::cout <<"incomingCall : " << ip <<" "<< port << std::endl;
  this->gui->incommingCall(user, ip, port);
}

void       Client::acceptCall(std::string const &user, std::string const &ip, std::string const &port)
{
  std::string data = user + ":" + this->hostname + ":" + std::to_string(this->udpPort);
  sendBabelPacket(Protocol::BabelPacket::Code::CALL_ACCEPTED, data);
  std::cout << ip << " " << port << std::endl;
  this->callerName = user;
  this->udpClient->setHostname(ip);
  this->udpClient->setPort(std::stoi(port));
  this->inCall = true;
  this->udpClient->initiateService();
  this->udpThread = this->spawn();
  this->udpThread.detach();
}

void       Client::hangUp(Protocol::BabelPacket const &packet)
{
  (void)packet;
  this->gui->setContactView();
//  this->packBuilder.getSoundControler().stopOutputStream();
  this->inCall = false;
//  this->udpThread.join();
}

void       Client::inCallThread()
{
//  this->packBuilder = new PackBuilder;
  this->packBuilder.getSoundControler().startInputStream();
  this->packBuilder.getSoundControler().startOutputStream();

  while (this->inCall)
  {
    EncPack pack = this->packBuilder.getEncoded();
    std::cout << pack.size << std::endl;
    if (pack.size > 0) {
      Protocol::BabelPacket *packet = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CALL_DATA,
                                                                       &pack.data[0], pack.size);
      this->udpClient->sendBabelPacket(*packet);
    }
//    delete this->packBuilder;
    //this->queue.pop();
//    std::this_thread::sleep_for (std::chrono::nanoseconds(1));
  }
  this->packBuilder.getSoundControler().stopOutputStream();
  this->packBuilder.getSoundControler().stopInputStream();
}

void       Client::callAccepted(Protocol::BabelPacket const &packet)
{
  std::string data(const_cast<char *>(reinterpret_cast<const char*>(packet.data)));
  this->callerName = data.substr(data.find(':') + 1);
  std::string ip = data.substr(0, data.find(':'));
  std::string port = data.substr(data.find(':') + 1);

  std::cout << "ip " << ip << ", port " << port << std::endl;

  this->udpClient->setHostname(ip);
  this->udpClient->setPort(std::stoi(port));
//  this->packBuilder.getSoundControler().startInputStream();
  //this->packBuilder.getSoundControler().startOutputStream();
  this->inCall = true;
  this->udpClient->initiateService();
  this->udpThread = this->spawn();
  this->udpThread.detach();
  this->gui->callAccepted(this->callerName);
}

void       Client::callDeclined(Protocol::BabelPacket const &packet)
{
  (void)packet;
  std::cout << "DECLINED !!!!!!!!!!" << std::endl;
  this->gui->setContactView();
}

void       Client::contactAdded(Protocol::BabelPacket const &packet)
{
  (void)packet;
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  if (this->tcpClient->sendBabelPacket(*newPacket) == false)
    this->gui->affInfoMessage("Server is not responding ...");
}

void       Client::endCall()
{
  this->inCall = false;
//  this->packBuilder.getSoundControler().stopOutputStream();
//  this->udpThread.join();
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket
          (Protocol::BabelPacket::Code::HANG_UP,
           Protocol::Protocol::stringToPointer(this->callerName), this->callerName.length());
  this->tcpClient->sendBabelPacket(*newPacket);
}

void       Client::contactDeleted(Protocol::BabelPacket const &packet)
{
  (void)packet;
  Protocol::BabelPacket   *newPacket = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  if (this->tcpClient->sendBabelPacket(*newPacket) == false)
    this->gui->affInfoMessage("Server is not responding ...");
}

void       Client::callPacket(Protocol::BabelPacket const &packet)
{
  EncPack pack;
  std::string data = Protocol::Protocol::extractData(packet);
  std::vector<unsigned char> v(data.begin(), data.end());
  pack.size = packet.dataLength;
  pack.data = v;
  this->packBuilder.setEncoded(pack);
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
  else if (packet.code == Protocol::BabelPacket::Code::USER_NOT_FOUND)
  {
    this->gui->affInfoMessage("User not found");
  }
  else if (packet.code == Protocol::BabelPacket::Code::SIGN_IN_FAILED)
  {
    this->gui->affInfoMessage("User not found, or incorrect password");
  }
    //this->gui->errorEncountered(error);
}
