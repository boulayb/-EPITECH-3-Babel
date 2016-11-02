#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <map>
#include "TCPServer.hpp"
#include "Protocol.hpp"

class TaskManager
{
public:
  struct Task
  {
    BabelPacket *packet;
    unsigned int clientID;
  };
  TaskManager();
  ~TaskManager();
  using taskFunction = void (TaskManager::*)(Task const &);
  void executeTask(Task const &task);
  void signInTask(Task const &);
  void signUpTask(Task const &);
  void signOutTask(Task const &);
  void getContactTask(Task const &);
  void callTask(Task const &);
  void delContactTask(Task const &);
  void addContactTask(Task const &);
  void updateContactStatusTask(Task const &);

  std::map<unsigned int, taskFunction> actions =
   {
     {BabelPacket::Code::SIGN_IN, &TaskManager::signInTask},
     {BabelPacket::Code::SIGN_UP, &TaskManager::signUpTask},
     {BabelPacket::Code::SIGN_OUT, &TaskManager::signOutTask},
     {BabelPacket::Code::CONTACT_LIST_REQUEST, &TaskManager::getContactTask},
     {BabelPacket::Code::CALL, &TaskManager::callTask},
     {BabelPacket::Code::DEL_CONTACT, &TaskManager::delContactTask},
     {BabelPacket::Code::ADD_CONTACT, &TaskManager::addContactTask},
     {BabelPacket::Code::UPDATE_CONTACT_STATUS, &TaskManager::updateContactStatusTask},
  };

private:
//  Database *database;
  TCPServer *network;
};

#endif // TASKMANAGER_HPP
