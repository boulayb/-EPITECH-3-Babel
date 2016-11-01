
//
// Created by bocque_c on 17/10/16.
//

#include "DataBase.h"

bool DataBase::registerUser(std::string const &login, std::string const &password)
{
    if (!this->checkIfUserExist(login))
        return (this->addNewUser(login, password));
    return false;
}

bool DataBase::login(std::string const &login, std::string const &password)
{
    return (this->checkUserInfo(login, password));
}

bool DataBase::addFriend(std::string const &login, std::string const &newFriend) {
    for (std::vector<std::string>::iterator it = this->_map[login].getFriendsNoConst().begin(); it != this->_map[login].getFriends().end(); ++it)
    {
        if (newFriend == *it)
            return false;
    }
    this->_map[login].getFriendsNoConst().push_back(newFriend);
    return true;
}

const std::vector<std::string> &DataBase::getFriendsList(std::string const &login)
{
    return (this->_map[login].getFriends());
}


DataBase::DataBase()
{
    bool continueRead = true;
    User user;

    std::ifstream ifile("/home/bocque_c/cpp_babel/tests/DataBase/rsc/database.txt"); //TODO : Fix relative Path
    boost::archive::binary_iarchive iTextArchive(ifile);
    while (continueRead)
    {
        try {
            iTextArchive >> user;
        }
        catch (boost::archive::archive_exception e) {
            continueRead = false;
        }
        if (continueRead)
            this->_map.insert(std::pair<std::string, User>(user.getLogin(), user));
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
    std::ofstream ofile("/home/bocque_c/cpp_babel/tests/DataBase/rsc/database.txt"); //TODO : Fix relative Path
    boost::archive::binary_oarchive oTextArchive(ofile);
    for(std::map<std::string, User>::const_iterator it = this->_map.begin(); it != this->_map.end(); ++it)
        oTextArchive << it->second;
    ofile.close();
    return true;
}
