#include <iostream>
#include "DataBase.h"

int main()
{
    std::vector<std::string> save;
    DataBase *base = new DataBase;
    if (base->registerUser("bocque", "passowrd"))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;

    if (base->login("bocque", "passowrd"))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;

    save = base->getFriendsList("bocque");
    for (std::vector<std::string>::iterator it = save.begin(); it != save.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    base->addFriend("bocque", "dimitri");
    base->addFriend("bocque", "arnaud");

    save = base->getFriendsList("bocque");

    for (std::vector<std::string>::iterator it = save.begin(); it != save.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    delete (base);
    return 0;
}
