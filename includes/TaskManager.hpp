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
  void updateContactStatusTask(int userId) const;

private:

  void signInTask(Task const &);
  void signUpTask(Task const &);
  void signOutTask(Task const &);
  void getContactTask(Task const &);
  void callTask(Task const &);
  void delContactTask(Task const &);
  void addContactTask(Task const &);

  std::map<Protocol::BabelPacket::Code, taskFunction> actions =
   {
     {Protocol::BabelPacket::Code::SIGN_IN, &TaskManager::signInTask},
     {Protocol::BabelPacket::Code::SIGN_UP, &TaskManager::signUpTask},
     {Protocol::BabelPacket::Code::SIGN_OUT, &TaskManager::signOutTask},
     {Protocol::BabelPacket::Code::CONTACT_LIST_REQUEST, &TaskManager::getContactTask},
     {Protocol::BabelPacket::Code::CALL, &TaskManager::callTask},
     {Protocol::BabelPacket::Code::DEL_CONTACT, &TaskManager::delContactTask},
     {Protocol::BabelPacket::Code::ADD_CONTACT, &TaskManager::addContactTask},
  };

  std::vector<std::string> &splitDataByDelimiter(char delimiter, unsigned char *data, int size);
  DataBase database;
  TCPServer *network;
  const int LOGIN_INDEX = 0;
  const int PASSWORD_INDEX = 1;
  const int STATUS_INDEX = 1;
  const int IP_INDEX = 1;
  const int PORT_INDEX = 2;
  const std::string ONLINE_STATUS = "online";
  const std::string OFFLINE_STATUS = "offline";
  const std::string ENDSEPARATOR = ";" ;
  const std::string SEPARATOR = ";" ;
};

#endif // TASKMANAGER_HPP
