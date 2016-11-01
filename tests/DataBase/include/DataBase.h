//
// Created by bocque_c on 17/10/16.
//

#ifndef BABELCE_DATABASE_H
#define BABELCE_DATABASE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
#include "User.h"

class DataBase {
public:
    DataBase();
    ~DataBase();
    bool registerUser(std::string const& login, std::string const& password);
    bool login(std::string const& login, std::string const& password);
    bool addFriend(std::string const& login, std::string const& newFriend);
    const std::vector<std::string>& getFriendsList(std::string const& login);
private:
    bool checkIfUserExist(std::string const& login);
    bool checkUserInfo(std::string const& login, std::string const& password);
    bool addNewUser(std::string const& login, std::string const& password);
    bool writeMap();
    std::map<std::string, User> _map;
};

#endif //BABELCE_DATABASE_H
