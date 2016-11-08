#include "gui.hh"
#include <iostream>
#include "Protocol.hpp"
#include "client.hpp"

Gui::Gui(int ac, char **av, Client *client) : app(ac, av)
{
    MainWindow *w = new MainWindow(this);
    this->mainWindow = w;
    this->client = client;
    w->show();
}

void    Gui::AddContact(std::string contactName)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::ADD_CONTACT, contactName);
}

void    Gui::askRegister(std::string username, std::string password)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::SIGN_UP, username, password);
}

void    Gui::askLogin(std::string username, std::string password)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::SIGN_IN, username, password);
}

void    Gui::askLogout()
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::SIGN_OUT);
}

void    Gui::call(std::string    contactName)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::CALL, contactName);
}

void    Gui::removeContact(std::string contactName)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::DEL_CONTACT, contactName);
}

void    Gui::newError(const std::string &error)
{
    this->mainWindow->newError(error);
}

void    Gui::Login()
{
    this->mainWindow->Login();
}

void    Gui::Logout()
{
    this->mainWindow->Logout();
}

void    Gui::UpdateContactList(std::vector<std::pair<std::string, bool>>    contactList)
{
    this->mainWindow->UpdateContactList(contactList);
}

void    Gui::UpdateContact(std::pair<std::__cxx11::string, bool>    contact)
{
    this->mainWindow->updateContact(contact);
}

void    Gui::incommingCall(const std::string &userName)
{
    if (mainWindow->incommingCall(userName))
        client->sendBabelPacket(Protocol::BabelPacket::Code::CALL_ACCEPTED);
    else
        client->sendBabelPacket(Protocol::BabelPacket::Code::CALL_DECLINED);

}

void    Gui::endCall()
{
    this->mainWindow->setInCall(false);
}

void    Gui::start()
{
    this->app.exec();
}
