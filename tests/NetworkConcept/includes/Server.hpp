#ifndef SERVER_H
#define SERVER_H

#include "TCPServer.hpp"
#include "TaskManager.hpp"
#include "ThreadPool.hpp"

class Server
{
public:
  Server();
  ~Server();
  void startServer();
  void addTask(Protocol::BabelPacket &, int clientId);
private:
  TCPServer *tcpServer;
  TaskManager taskManager;
  ThreadPool<TaskManager::Task>  threadPool;
};

#endif // SERVER_H
