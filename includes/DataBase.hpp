//
// Created by bocque_c on 17/10/16.
//

#ifndef BABELCE_DATABASE_HPP
# define BABELCE_DATABASE_HPP
# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <map>
# include <iterator>
# include <utility>
# include "User.hpp"
# include "Protocol.hpp"

class DataBase {
public:
    DataBase();
    ~DataBase();
    Protocol::BabelPacket::Code registerUser(std::string const& login, std::string const& password);
    Protocol::BabelPacket::Code login(std::string const& login, std::string const& password);
    Protocol::BabelPacket::Code addFriend(std::string const& login, std::string const& newFriend);
    Protocol::BabelPacket::Code deleteFriend(std::string const &login, std::string const &newFriend);
    void addText(std::string const &login, std::string const &text);
    std::vector<std::string>& getTexts(std::string const &login) const;
    const std::vector<std::string>& getFriendsList(std::string const& login) const;
    void setId(std::string const &login, int id);
    int getId(std::string const &login) const;
    std::string const &getLoginById(int id) const;

private:
    bool checkIfUserExist(std::string const& login) const;
    bool addNewUser(std::string const& login, std::string const& password);
    bool writeMap();
    std::map<std::string, User> _map;
    const std::string DATABASE_PATH = "database.bin";
};

#endif //BABELCE_DATABASE_HPP
