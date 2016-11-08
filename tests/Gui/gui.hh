#ifndef GUI_HH
#define GUI_HH

#include "mainwindow.h"

class client;

class Gui
{
public:
    Gui(int ac, char **av, Client *client);
    ~Gui() {};


    void    AddContact(std::string contactName);
    void    askRegister(std::string username, std::string password);
    void    askLogin(std::string username, std::string password);
    void    askLogout();
    void    call(std::string contactName);
    void    removeContact(std::string contacName);
    void    newError(const std::string &error);

    void    UpdateContactList(std::vector<std::pair<std::string, bool>>);
    void    UpdateContact(std::pair<std::string, bool>);
    void    Logout();
    void    Login();

    void    incommingCall(const std::string &userName);
    void    endCall();
    void    answerCall();



private:
    MainWindow  *mainWindow;
    Client      *client;
};

#endif // GUI_HH
