#ifndef TASKMANAGER_HPP
# define TASKMANAGER_HPP

# include <map>
# include "DataBase.hpp"
# include "TCPServer.hpp"
# include "Protocol.hpp"

class TaskManager
{
public:
  struct Task
  {
    Protocol::BabelPacket *packet;
    unsigned int clientID;
  };
  TaskManager();
  ~TaskManager();
  typedef void (TaskManager::*taskFunction)(Task const &);
  void executeTask(Task const &task);
  void signInTask(Task const &);
  void signUpTask(Task const &);
  void signOutTask(Task const &);
  void getContactTask(Task const &);
  void callTask(Task const &);
  void delContactTask(Task const &);
  void addContactTask(Task const &);
  void updateContactStatusTask(Task const &);

  std::map<Protocol::BabelPacket::Code, taskFunction> actions =
   {
     {Protocol::BabelPacket::Code::SIGN_IN, &TaskManager::signInTask},
     {Protocol::BabelPacket::Code::SIGN_UP, &TaskManager::signUpTask},
     {Protocol::BabelPacket::Code::SIGN_OUT, &TaskManager::signOutTask},
     {Protocol::BabelPacket::Code::CONTACT_LIST_REQUEST, &TaskManager::getContactTask},
     {Protocol::BabelPacket::Code::CALL, &TaskManager::callTask},
     {Protocol::BabelPacket::Code::DEL_CONTACT, &TaskManager::delContactTask},
     {Protocol::BabelPacket::Code::ADD_CONTACT, &TaskManager::addContactTask},
     {Protocol::BabelPacket::Code::UPDATE_CONTACT_STATUS, &TaskManager::updateContactStatusTask}
  };

private:
  std::vector<std::string> &splitDataByDelimiter(char delimiter, char *data, int size);
  DataBase *database;
  TCPServer *network;
  const int LOGIN_INDEX = 0;
  const int PASSWORD_INDEX = 0;
};

#endif // TASKMANAGER_HPP
