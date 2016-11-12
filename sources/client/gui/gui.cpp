#include "gui.hh"
#include <iostream>
#include "Protocol.hpp"
#include "client.hpp"

Gui::Gui(int ac, char **av) : app(ac, av)
{
    MainWindow *w = new MainWindow(this);
    this->mainWindow = w;
    this->mainWindow->askNetworkInfo();
    w->show();
}

void   Gui::setClient(Client *client)
{
  this->client = client;
}

void    Gui::AddContact(const std::string &contactName)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::ADD_CONTACT, contactName);
}

void    Gui::askRegister(const std::string &username, const std::string &password)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::SIGN_UP, username, password);
}

void    Gui::askLogin(const std::string &username, const std::string &password)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::SIGN_IN, username, password);
}

void    Gui::askLogout()
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::SIGN_OUT);
}

void    Gui::call(const std::string &contactName)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::CALL, contactName);
}

void    Gui::removeContact(const std::string &contactName)
{
    client->sendBabelPacket(Protocol::BabelPacket::Code::DEL_CONTACT, contactName);
}

void    Gui::newError(const std::string &error)
{
    this->mainWindow->newError(error);
}

void    Gui::Login()
{
    std::cout << "login qt" << std::endl;
    this->mainWindow->Login();
}

void    Gui::setLoginView()
{
    this->mainWindow->setLoginView();
}

void    Gui::UpdateContactList(std::vector<std::pair<std::string, bool>>    contactList)
{
    this->mainWindow->UpdateContactList(contactList);
}

void    Gui::UpdateContact(const std::pair<std::string, bool>    &contact)
{
    this->mainWindow->updateContact(contact);
}

void    Gui::incommingCall(const std::string &userName, const std::string &ip, const std::string &port)
{
    if (mainWindow->incommingCall(userName))
      client->acceptCall(userName, ip, port);
    else
      client->sendBabelPacket(Protocol::BabelPacket::Code::CALL_DECLINED, userName);

}

void    Gui::callAccepted()
{
  this->mainWindow->setInCall(true);
}

void    Gui::affInfoMessage(std::string const & msg)
{
  this->mainWindow->affInfoMessage(msg);
}

void    Gui::endCall()
{
    this->mainWindow->setInCall(false);
}

void    Gui::start()
{
  this->app.exec();
}
