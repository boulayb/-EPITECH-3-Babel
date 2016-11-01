#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include "Session.hpp"
#include "INetwork.hpp"
#include "TaskManager.hpp"
#include "ThreadPool.hpp"
#include <vector>

class TCPServer : public INetwork
{
public:
  TCPServer(unsigned short port);
  ~TCPServer();
  bool initiateService();
  void shutDown();
  bool sendBabelPacket(BabelPacket &);
private:
  void handle_accept(Session* new_session,
      const boost::system::error_code& error);
  void startAccept();

  boost::asio::io_service ioService;
  boost::asio::ip::tcp::acceptor acceptor;
  std::vector<Session *> users;
  TaskManager taskManager;
  ThreadPool<TaskManager::Task>  threadPool;
  unsigned int maxUserId;
};

#endif // TCPSERVER_HPP
