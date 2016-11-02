#ifndef GUI_HH
#define GUI_HH

#include "mainwindow.h"

class Gui
{
public:
    Gui(int ac, char **av);
    ~Gui() {};

    //void    UpdateContactList(std::vector<std::string>);
    bool    AddContact(std::string contactName);
    bool    askRegister(std::string username, std::string password);
    bool    askLogin(std::string username, std::string password);
    void    logout();
    bool    call(std::string contactName);
    void    endCall();
    void    removeContact(std::string contacName);
    void    newError(const std::string &error);

private:
    MainWindow  *mainWindow;
};

#endif // GUI_HH
