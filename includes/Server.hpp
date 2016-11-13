#ifndef SERVER_H
#define SERVER_H

#include "TCPServer.hpp"
#include "TaskManager.hpp"
#include "ThreadPool.hpp"

class Server
{
public:
  Server(int port = 4000);
  ~Server();
  void startServer();
  void addTask(Protocol::BabelPacket &, int clientId);
  const TaskManager &getTaskManager() const;
private:
  TCPServer *tcpServer;
  TaskManager *taskManager;
  ThreadPool<TaskManager::Task>  threadPool;
};

#endif // SERVER_H
