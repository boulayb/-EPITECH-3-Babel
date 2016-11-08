
//
// Created by bocque_c on 17/10/16.
//

#include "DataBase.h"

Protocol::BabelPacket::Code DataBase::registerUser(std::string const &login, std::string const &password)
{
    if (this->checkIfUserExist(login))
      return (Protocol::BabelPacket::Code::USER_ALREADY_EXIST);
    this->addNewUser(login, password);
    return (Protocol::BabelPacket::Code::SIGN_UP_SUCCESS);
}

Protocol::BabelPacket::Code DataBase::login(std::string const &login, std::string const &password)
{
    if (this->_map[login].getLogin() != login)
      return (Protocol::BabelPacket::Code::USER_NOT_FOUND);
    if (this->_map[login].getPassword() != password)
      return (Protocol::BabelPacket::Code::WRONG_PASSWORD);
    return (Protocol::BabelPacket::Code::LOGIN_SUCCESS);
}

std::string &DataBase::getLoginById(int id)
{
}

void DataBase::setId(std::string const &login, int id)
{
    if (this->_map[login].getLogin() == login)
      this->_map[login].setId(id);
}

int DataBase::getId(std::string const &login)
{
    if (this->_map[login].getLogin() != login)
      return (-1);
    return (this->_map[login].getId());
}

Protocol::BabelPacket::Code DataBase::addFriend(std::string const &login, std::string const &newFriend)
{
    if (this->_map[login].getLogin() != login)
      return (Protocol::BabelPacket::Code::USER_NOT_FOUND);
    for (std::vector<std::string>::iterator it = this->_map[login].getFriends().begin(); it != this->_map[login].getFriends().end(); ++it)
    {
        if (newFriend == *it)
            return (Protocol::BabelPacket::Code::ALREADY_A_FRIEND);
    }
    this->_map[login].getFriends().push_back(newFriend);
    return (Protocol::BabelPacket::Code::CONTACT_ADDED);
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
            return (Protocol::BabelPacket::Code::CONTACT_DELETED);
        }
    }
    return (Protocol::BabelPacket::Code::FRIEND_NOT_FOUND);
}

const std::vector<std::string> &DataBase::getFriendsList(std::string const &login)
{
    return (this->_map[login].getFriends());
}


DataBase::DataBase()
{
    bool continueRead = true;
    User user;
    std::ifstream ifile("/home/bocque_c/rendu/cpp_babel/tests/DataBase/rsc/database55.txt", std::fstream::in);

    /*if (!ifile.is_open())
    {
      std::cout << "not open" << std::endl;
      ifile.close();
      std::ofstream o("/home/bocque_c/rendu/cpp_babel/tests/DataBase/rsc/database3.txt");
      o << "pepe" << std::endl;
      o << fflush;
      o.close();
      std::ifstream ifile("/home/bocque_c/rendu/cpp_babel/tests/DataBase/rsc/database3.txt");
    }*/

    if (!ifile.is_open())
    {
      std::cout << "still not open again" << std::endl;
    }

    try{
        boost::archive::binary_iarchive iTextArchive(ifile);
        while (true)
        {
            iTextArchive >> user;
            this->_map.insert(std::pair<std::string, User>(user.getLogin(), user));
        }
    }
    catch (boost::archive::archive_exception e)
    {
    }
    ifile.close();
}

DataBase::~DataBase()
{
    this->writeMap();
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
    std::ofstream ofile("/home/bocque_c/rendu/cpp_babel/tests/DataBase/rsc/database55.txt"); //TODO : Fix relative Path
    boost::archive::binary_oarchive oTextArchive(ofile);
    for(std::map<std::string, User>::const_iterator it = this->_map.begin(); it != this->_map.end(); ++it)
        oTextArchive << it->second;
    ofile.close();
    return true;
}
