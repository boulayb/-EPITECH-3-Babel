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
  std::vector<std::string> *dataSplited = this->splitDataByDelimiter(':', task.packet->data, task.packet->dataLengh);
  BabelPacket::Code returnCode = this->database->login(dataSplited[LOGIN_INDEX], password[PASSWORD_INDEX]);
  BabelPacket *packet = Protocol::Protocol::createPacket(returnCode, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
}

void TaskManager::signUpTask(Task const &task)
{
  std::vector<std::string> *dataSplited = this->splitDataByDelimiter(':', task.packet->data, task.packet->dataLengh);
  BabelPacket::Code returnCode = this->database->registerUser(dataSplited[LOGIN_INDEX], password[PASSWORD_INDEX]);
  BabelPacket *packet = Protocol::Protocol::createPacket(returnCode, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
}

void TaskManager::signOutTask(Task const &task)
{
  std::string login = this->getLoginById(task.clientID);
  this->database->setID(login, -1);
  BabelPacket *packet = Protocol::Protocol::createPacket(BabelPacket::Code::DISCONNECT_SUCCESS, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
  this->network->disconnectUser(task.clientID);
}

void TaskManager::getContactTask(Task const &)
{
  std::vector<std::string> *dataSplited = this->splitDataByDelimiter(':', task.packet->data, task.packet->dataLengh);
  BabelPacket::Code returnCode = this->database->getFriendsList(dataSplited[LOGIN_INDEX], password[PASSWORD_INDEX]);
  BabelPacket *packet = Protocol::Protocol::createPacket(returnCode, nullptr, 0);
  this->network->sendBabelPacket(*packet, task.clientID);
}

void TaskManager::callTask(Task const &)
{

}

void TaskManager::delContactTask(Task const &)
{

}

void TaskManager::addContactTask(Task const &)
{

}

void TaskManager::updateContactStatusTask(Task const &)
{

}

std::vector<std::__cxx11::string> &TaskManager::splitDataByDelimiter(char delimiter, char *data, int size)
{
  std::vector<std::string> *dataSplited = new std::vector<std::string>;
  int nbrWords = 0;
  for (int i = 0; i < size ; ++i)
  {
    if (data[i] == delimiter)
      nbrWords++;
    else
      dataSplited[nbrWords] += data[i];
  }
  return *dataSplited;
}
