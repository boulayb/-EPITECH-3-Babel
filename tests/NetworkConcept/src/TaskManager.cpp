#include <iostream>
#include <exception>
#include "TaskManager.hpp"

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

void TaskManager::executeTask(Task const &task)
{
  auto it = this->actions.find(task.packet->code);

  if (it != this->actions.end())
  {
    (this->*(it->second))(task);
  }
//  else
    // Send something to client to make him shut up
}

void TaskManager::signInTask(Task const &task)
{
  std::vector<std::string> dataSplited = this->splitDataByDelimiter(':', reinterpret_cast<char*>(task.packet->data), task.packet->dataLength);
  Protocol::BabelPacket::Code returnCode = this->database->login(dataSplited[LOGIN_INDEX], dataSplited[PASSWORD_INDEX]);
  Protocol::BabelPacket *packet = Protocol::Protocol::createPacket(returnCode, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
}

void TaskManager::signUpTask(Task const &task)
{
  std::vector<std::string> dataSplited = this->splitDataByDelimiter(':', reinterpret_cast<char*>(task.packet->data), task.packet->dataLength);
  Protocol::BabelPacket::Code returnCode = this->database->registerUser(dataSplited[LOGIN_INDEX], dataSplited[PASSWORD_INDEX]);
  Protocol::BabelPacket *packet = Protocol::Protocol::createPacket(returnCode, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
}

void TaskManager::signOutTask(Task const &task)
{
  std::string login = this->database->getLoginById(task.clientID);
  this->database->setId(login, -1);
  Protocol::BabelPacket *packet = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::DISCONNECT_SUCCESS, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
  this->network->disconnectUser(task.clientID);
}

void TaskManager::getContactTask(Task const &task)
{
  std::vector<std::string> dataSplited = this->splitDataByDelimiter(':', reinterpret_cast<char*>(task.packet->data), task.packet->dataLength);
  const std::vector<std::string> &returnCode = this->database->getFriendsList(dataSplited[LOGIN_INDEX]);
  Protocol::BabelPacket *packet = Protocol::Protocol::createPacket(Protocol::BabelPacket::Code::CONTACT_LIST, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
}

void TaskManager::callTask(Task const &task)
{

}

void TaskManager::delContactTask(Task const &task)
{

}

void TaskManager::addContactTask(Task const &task)
{

}

void TaskManager::updateContactStatusTask(Task const &task)
{

}

std::vector<std::__cxx11::string> &TaskManager::splitDataByDelimiter(char delimiter, char *data, int size)
{
  std::vector<std::string> *dataSplited = new std::vector<std::string>;
  int nbrWords = 0;
  std::string word = "";
  for (int i = 0; i < size ; ++i)
  {
    if (data[i] == delimiter)
      {
	nbrWords++;
	dataSplited->push_back(word);
	word = "";
      }
    else
      word += data[i];
  }
  return *dataSplited;
}
