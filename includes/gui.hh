#ifndef GUI_HH
#define GUI_HH

#include <QApplication>
#include "mainwindow.h"
#include "client.hpp"

class client;

class Gui
{
public:
    Gui(int ac, char **av);
    ~Gui() {};

    void    start();
    void    setClient(Client *client);
    void    AddContact(std::string contactName);
    void    askRegister(std::string username, std::string password);
    void    askLogin(std::string username, std::string password);
    void    askLogout();
    void    call(std::string contactName);
    void    removeContact(std::string contacName);
    void    newError(const std::string &error);

    void    UpdateContactList(std::vector<std::pair<std::string, bool>>);
    void    UpdateContact(std::pair<std::string, bool>);
    void    setLoginView();
    void    Login();
    void    affInfoMessage(std::string const &);
    void    incommingCall(const std::string &userName);
    void    endCall();
    void    answerCall();



private:
    MainWindow  *mainWindow;
    Client      *client;
    QApplication app;
};

#endif // GUI_HH
