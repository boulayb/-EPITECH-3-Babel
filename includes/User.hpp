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
        (void)version;
        ar & _login & _password & _friends & _texts;
    }
    User();
    User(std::string const& login, std::string const& password);
    ~User();
    std::string const& getLogin() const;
    std::string const& getPassword() const;
    int getId() const;
    void setId(int id);
    const std::vector<std::string> & getFriends() const;
    std::vector<std::string> & getFriends();
    std::vector<std::string> & getTexts() const;

private:
    std::string _login;
    std::string _password;
    std::vector<std::string> _friends;
    std::vector<std::string> _texts;
    int _id;
};


#endif //BABELCE_USER_H
