#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <map>
#include "Protocol.hpp"
#include "INetwork.hpp"

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
  using taskFunction = void (TaskManager::*)(BabelPacket const &);
  void executeTask(Task const &task);
  void signInTask(BabelPacket const &);
  void signUpTask(BabelPacket const &);
  void signOutTask(BabelPacket const &);
  void getContactTask(BabelPacket const &);
  void callTask(BabelPacket const &);
  void delContactTask(BabelPacket const &);
  void addContactTask(BabelPacket const &);
  void updateContactStatusTask(BabelPacket const &);

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
  INetwork *network;
};

#endif // TASKMANAGER_HPP
