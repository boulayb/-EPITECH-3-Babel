#include "Server.hpp"

Server::Server()
{
  this->tcpServer = new TCPServer(this, 4001);
}

Server::~Server()
{

}

void Server::startServer()
{
  this->tcpServer->initiateService();
}

void Server::addTask(BabelPacket &packet, int clientId)
{
  TaskManager::Task *newTask = new TaskManager::Task;
  newTask->packet = &packet;
  newTask->clientID = clientId;
  this->threadPool.putTaskInQueue(std::bind(&TaskManager::executeTask, this->taskManager, *newTask),
                                   *newTask);
}
