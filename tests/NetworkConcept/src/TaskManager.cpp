#include <iostream>
#include <exception>
#include "TaskManager.hpp"

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

void TaskManager::executeTask(Task const &task)
{
  auto it = this->actions.find(task.packet->code);

  if (it != this->actions.end())
  {
    (this->*(it->second))(task);
  }
//  else
    // Send something to client to make him shut up
}

void TaskManager::signInTask(Task const &)
{

}

void TaskManager::signUpTask(Task const &)
{

}

void TaskManager::signOutTask(Task const &)
{

}

void TaskManager::getContactTask(Task const &)
{

}

void TaskManager::callTask(Task const &)
{

}

void TaskManager::delContactTask(Task const &)
{

}

void TaskManager::addContactTask(Task const &)
{

}

void TaskManager::updateContactStatusTask(Task const &)
{

}
