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
  TaskManager(TCPServer *);
  ~TaskManager();
  typedef void (TaskManager::*taskFunction)(Task const &);
  void executeTask(Task const &task);
  void updateContactStatusTask(std::string const &, std::string const &) const;
private:

  void handShakeTask(Task const &);
  void signInTask(Task const &);
  void connectionLostTask(Task const &task);
  void signUpTask(Task const &);
  void signOutTask(Task const &);
  void getContactTask(Task const &);
  void callTask(Task const &);
  void delContactTask(Task const &);
  void addContactTask(Task const &);
  void callAcceptedTask(Task const &);
  void callDeclinedTask(Task const &);
  void handShakeSuccess(Task const &);

  std::map<Protocol::BabelPacket::Code, taskFunction> actions =
   {
     {Protocol::BabelPacket::Code::HAND_SHAKE, &TaskManager::handShakeTask},
     {Protocol::BabelPacket::Code::SIGN_IN, &TaskManager::signInTask},
     {Protocol::BabelPacket::Code::SIGN_UP, &TaskManager::signUpTask},
     {Protocol::BabelPacket::Code::INVALID_REQUEST, &TaskManager::connectionLostTask},
     {Protocol::BabelPacket::Code::SIGN_OUT, &TaskManager::signOutTask},
     {Protocol::BabelPacket::Code::CONTACT_LIST, &TaskManager::getContactTask},
     {Protocol::BabelPacket::Code::CALL, &TaskManager::callTask},
     {Protocol::BabelPacket::Code::DEL_CONTACT, &TaskManager::delContactTask},
     {Protocol::BabelPacket::Code::ADD_CONTACT, &TaskManager::addContactTask},
     {Protocol::BabelPacket::Code::CALL_ACCEPTED, &TaskManager::callAcceptedTask},
     {Protocol::BabelPacket::Code::HAND_SHAKE_SUCCESS, &TaskManager::handShakeSuccess},
     {Protocol::BabelPacket::Code::CALL_DECLINED, &TaskManager::callDeclinedTask}
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
  const std::string SEPARATOR = ":" ;
};

#endif // TASKMANAGER_HPP
