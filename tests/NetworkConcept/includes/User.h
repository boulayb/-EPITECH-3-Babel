//
// Created by bocque_c on 31/10/16.
//

#ifndef BABELCE_USER_H
# define BABELCE_USER_H
#  include <cstring>
#  include <string>
#  include <vector>
#  include <boost/archive/binary_iarchive.hpp>
#  include <boost/archive/binary_oarchive.hpp>
#  include <boost/archive/text_iarchive.hpp>
#  include <boost/archive/text_oarchive.hpp>
#  include <boost/serialization/vector.hpp>

class User
{
public:
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & _login & _password & _friends & _id;
    }
    User();
    User(std::string const& login, std::string const& password);
    ~User();
    std::string const& getLogin();
    std::string const& getPassword();
    int getId();
    void setId(int id);
    //const std::vector<std::string> & getFriends(); TODO:Overload this function
    std::vector<std::string> & getFriends();
private:
    std::string _login;
    std::string _password;
    std::vector<std::string> _friends;
    int _id;
};


#endif //BABELCE_USER_H
