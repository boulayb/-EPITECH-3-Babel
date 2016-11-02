#include "gui.hh"
#include <QApplication>
#include <iostream>

Gui::Gui(int ac, char **av)
{
    QApplication  app(ac, av);
    MainWindow *w = new MainWindow(this);
    this->mainWindow = w;
    w->show();

    app.exec();
}

bool    Gui::AddContact(std::string contactName)
{
    (void) contactName;
    return true;
}

bool    Gui::askRegister(std::string username, std::string password)
{
    (void) username;
    (void) password;
    return true;
}

bool    Gui::askLogin(std::string username, std::string password)
{
    (void) username;
    (void) password;
    return true;
}

void    Gui::logout()
{
}

bool    Gui::call(std::string    contactName)
{
    (void) contactName;
    return (true);
}

void    Gui::endCall()
{

}

void    Gui::removeContact(std::string contactName)
{
    (void) contactName;
}

void    Gui::newError(const std::string &error)
{
    this->mainWindow->newError(error);
}
