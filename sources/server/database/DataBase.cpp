//
// Created by bocque_c on 17/10/16.
//

#include "DataBase.hpp"

DataBase::DataBase()
{
  User user;

  std::ifstream file(DATABASE_PATH, std::fstream::in);
  if (file.is_open())
  {
    try {
      boost::archive::binary_iarchive iTextArchive(file);
      while (true) {
        iTextArchive >> user;
        this->_map.insert(std::pair<std::string, User>(user.getLogin(), user));
      }
    }
    catch (boost::archive::archive_exception e) {
    }
  }
  else
  {
    std::cerr << "Can't open file  : " << DATABASE_PATH << std::endl;
    exit(EXIT_FAILURE);
  }

  file.close();
}

DataBase::~DataBase()
{
  this->writeMap();
}

Protocol::BabelPacket::Code DataBase::registerUser(std::string const &login, std::string const &password)
{
  if (this->checkIfUserExist(login))
    return (Protocol::BabelPacket::Code::USER_ALREADY_EXIST);
  this->addNewUser(login, password);
  this->writeMap();
  return (Protocol::BabelPacket::Code::SIGN_UP_SUCCESS);
}

Protocol::BabelPacket::Code DataBase::login(std::string const &login, std::string const &password)
{
  if (this->_map[login].getLogin() != login)
    return (Protocol::BabelPacket::Code::SIGN_IN_FAILED);
  if (this->_map[login].getPassword() != password)
    return (Protocol::BabelPacket::Code::SIGN_IN_FAILED);
  return (Protocol::BabelPacket::Code::SIGN_IN_SUCCESS);
}

std::string const &DataBase::getLoginById(int id) const
{
  std::cout << "wtf" << this->_map.size() <<std::endl;
  for (std::pair<std::string, User> p : this->_map)
  {
    std::cout << "wtf" << std::endl;
    if (p.second.getId() == id)
      return p.second.getLogin();
  }
  throw std::exception();
}

Protocol::BabelPacket::Code DataBase::setId(std::string const &login, int id)
{
  if (this->_map[login].getLogin() != login)
    return (Protocol::BabelPacket::Code::USER_NOT_FOUND);
  this->_map[login].setId(id);
  return (Protocol::BabelPacket::Code::SIGN_UP_SUCCESS);
}

int DataBase::getId(std::string const &login) const
{
  std::map<std::string, User>::const_iterator it = this->_map.find(login);
  if (it != this->_map.end())
    return (this->_map.at(login).getId());
  return (-1);
}

Protocol::BabelPacket::Code DataBase::addFriend(std::string const &login, std::string const &newFriend)
{
  if (this->_map[login].getLogin() != login)
    return (Protocol::BabelPacket::Code::USER_NOT_FOUND);
  for (std::vector<std::string>::iterator it = this->_map[login].getFriends().begin(); it != this->_map[login].getFriends().end(); ++it)
  {
      if (newFriend == *it)
          return (Protocol::BabelPacket::Code::USER_ALREADY_FRIEND);
  }
  this->_map[login].getFriends().push_back(newFriend);
  this->writeMap();
  return (Protocol::BabelPacket::Code::CONTACT_ADD_SUCCESS);
}

Protocol::BabelPacket::Code DataBase::deleteFriend(std::string const &login, std::string const &newFriend)
{
  if (this->_map[login].getLogin() != login)
    return (Protocol::BabelPacket::Code::USER_NOT_FOUND);
  for (std::vector<std::string>::iterator it = this->_map[login].getFriends().begin(); it != this->_map[login].getFriends().end(); ++it)
  {
    if (newFriend == *it)
    {
        this->_map[login].getFriends().erase(it);
      this->writeMap();
      return (Protocol::BabelPacket::Code::CONTACT_DEL_SUCCESS);
    }
  }
  return (Protocol::BabelPacket::Code::USER_NOT_FRIEND);
}

const std::vector<std::string> &DataBase::getFriendsList(std::string const &login) const
{
  std::map<std::string, User>::const_iterator it = this->_map.find(login);
  if (it != this->_map.end())
    return (this->_map.at(login).getFriends());
  throw std::exception();
}

bool DataBase::checkIfUserExist(std::string const &login)
{
  std::map<std::string, User>::const_iterator it = this->_map.find(login);
  return it!=this->_map.end();
}

bool DataBase::checkUserInfo(std::string const &login, std::string const &password)
{
  return (this->_map[login].getPassword() == password);
}

bool DataBase::addNewUser(std::string const &login, std::string const &password)
{
  User user(login, password);
  this->_map.insert(std::pair<std::string, User>(login, user));
  return (true);
}

bool DataBase::writeMap()
{
  std::ofstream ofile(DATABASE_PATH);
  boost::archive::binary_oarchive oTextArchive(ofile);
  for(std::map<std::string, User>::const_iterator it = this->_map.begin(); it != this->_map.end(); ++it)
      oTextArchive << it->second;
  ofile.close();
  return true;
}
