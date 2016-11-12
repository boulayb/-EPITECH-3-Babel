#ifndef GUI_HH
#define GUI_HH

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QApplication>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

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
    void    AddContact(const std::string &contactName);
    void    askRegister(const std::string &username, const std::string &password);
    void    askLogin(const std::string &username, const std::string &password);
    void    askLogout();
    void    call(const std::string &contactName);
    void    removeContact(const std::string &contacName);
    void    newError(const std::string &error);

    void    UpdateContactList(std::vector<std::pair<std::string, bool>>);
    void    UpdateContact(const std::pair<std::string, bool> &contact);
    void    setLoginView();
    void    Login();
    void    affInfoMessage(std::string const &);
    void    incommingCall(const std::string &userName, const std::string &ip, const std::string &port);
    void    endCall();
    void    answerCall();
    void    callAccepted();
    const std::pair<std::string, int> &getNetworkInfo() const;


private:
    MainWindow  *mainWindow;
    Client      *client;
    QApplication app;
};

#endif // GUI_HH
