#include "TaskManager.hpp"
#include <iostream>

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

void TaskManager::executeTask(Task const &task)
{
  std::cout << "CYKA BLIAT DAVAI DAVAI" << std::endl;
  std::cout << task.clientID << std::endl;
}

void TaskManager::signInTask(const BabelPacket &)
{

}

void TaskManager::signUpTask(const BabelPacket &)
{

}

void TaskManager::signOutTask(const BabelPacket &)
{

}

void TaskManager::getContactTask(const BabelPacket &)
{

}

void TaskManager::callTask(const BabelPacket &)
{

}

void TaskManager::delContactTask(const BabelPacket &)
{

}

void TaskManager::addContactTask(const BabelPacket &)
{

}

void TaskManager::updateContactStatusTask(const BabelPacket &)
{

}
