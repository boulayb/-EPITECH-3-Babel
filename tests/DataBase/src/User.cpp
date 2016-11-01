//
// Created by bocque_c on 31/10/16.
//

#include "User.h"

User::User(std::string const& login, std::string const& password) {
    this->_login = login;
    this->_password = password;
}

User::~User() {

}

User::User() {
    this->_login = "";
    this->_password = "";
}

std::string const &User::getLogin()
{
    return (this->_login);
}

std::string const &User::getPassword()
{
    return (this->_password);
}

const std::vector<std::string> & User::getFriends()
{
    return (this->_friends);
}

std::vector<std::string> & User::getFriendsNoConst()
{
    return (this->_friends);
}