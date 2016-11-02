#include <iostream>
#include "DataBase.h"
#include "Protocol.h"

int main()
{
    std::vector<std::string> save;
    DataBase *base = new DataBase;
    /*if (Protocol::BabelPacket::Code::USER_ALREADY_EXIST == base->registerUser("bocque", "passowrd"))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;

    if (base->login("bocque", "passowrd"))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;*/

    save = base->getFriendsList("bocque");
    for (std::vector<std::string>::iterator it = save.begin(); it != save.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    //base->addFriend("bocque", "dimitri");
    base->deleteFriend("bocque", "arnaud");
    std::cout << std::endl;
    save = base->getFriendsList("bocque");

    for (std::vector<std::string>::iterator it = save.begin(); it != save.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    delete (base);
    return 0;
}
