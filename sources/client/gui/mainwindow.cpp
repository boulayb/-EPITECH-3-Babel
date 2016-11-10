#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QListWidget>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui.hh"
#include <iostream>
#include "mycontactlistitem.h"
#include "Protocol.hpp"

MainWindow::MainWindow(Gui *gui, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->gui = gui;
    ui->setupUi(this);
    ui->Stack->setCurrentIndex(0);
    ui->ErrorLogin->setVisible(false);
    connect(ui->loginButton, SIGNAL (released()), this, SLOT (LoginButton()));
    connect(ui->RegisterButton, SIGNAL (released()), this, SLOT (RegisterButton()));
    connect(ui->CancelRegisterButton, SIGNAL (released()), this, SLOT (CancelRegisterButton()));
    connect(ui->LogoutButton, SIGNAL (released()), this, SLOT (LogoutButton()));
    connect(ui->RegisterRegisterButton, SIGNAL (released()), this, SLOT (RegisterRegisterButton()));
    connect(ui->AddContactButton, SIGNAL (released()), this, SLOT (AddContactButton()));
    connect(ui->CallButton, SIGNAL (released()), this, SLOT (callButton()));
    connect(ui->EndCallButton, SIGNAL (released()), this, SLOT (endCallButton()));
    connect(ui->ContactList, SIGNAL (itemSelectionChanged()), this, SLOT (selectContact()));
    connect(ui->RemoveContactButton, SIGNAL (released()), this, SLOT (removeContactButton()));
    ui->RemoveContactButton->setDisabled(true);
    this->inCall = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void        MainWindow::LoginButton()
{
    if (ui->PasswordLogInput->text().isEmpty())
          QMessageBox::information(this,"Error","Password empty");
    else if (ui->UsernameLogInput->text().isEmpty())
          QMessageBox::information(this,"Error","Username empty");
    else
    {
        QByteArray password = this->hash->hash(ui->PasswordLogInput->text().toUtf8(),QCryptographicHash::Md5);
        QString passwordHash(password.toHex());

        this->gui->askLogin(ui->UsernameLogInput->text().toUtf8().constData(), ui->PasswordLogInput->text().toUtf8().constData());
    }
}

void        MainWindow::Login()
{
    std::cout << ":pepe:" << std::endl;
    ui->Stack->setCurrentIndex(2);
    std::cout << ":pepe2:" << std::endl;
}

void        MainWindow::RegisterRegisterButton()
{
    if (ui->UsernameRegisterInput->text().isEmpty())
        QMessageBox::information(this,"Error","Username empty");
    else if (ui->PasswordRegisterFirstInput->text().isEmpty() || ui->PasswordRegisterSecInput->text().isEmpty())
        QMessageBox::information(this,"Error","One Password is empty");
    else if (ui->PasswordRegisterFirstInput->text().compare(ui->PasswordRegisterSecInput->text()) != 0)
         QMessageBox::information(this,"Error","Passwords are differents");
    else
    {
        QByteArray password = this->hash->hash(ui->PasswordRegisterFirstInput->text().toUtf8(),QCryptographicHash::Md5);
        QString passwordHash(password.toHex());
        this->gui->askRegister(ui->UsernameRegisterInput->text().toUtf8().constData(), ui->PasswordRegisterFirstInput->text().toUtf8().constData());
        //QMessageBox::information(this, "Succes", "Sent registering request");
    }
}

void        MainWindow::RegisterButton()
{
    ui->Stack->setCurrentIndex(1);
}

void        MainWindow::CancelRegisterButton(){
    ui->Stack->setCurrentIndex(0);
}

void        MainWindow::LogoutButton()
{
    if (!inCall)
        this->gui->askLogout();
}

void        MainWindow::setLoginView()
{
    ui->Stack->setCurrentIndex(0);
}

void        MainWindow::affInfoMessage(std::string const & msg)
{
  QMessageBox::information(this, "Info", msg.c_str());
}

void    MainWindow::AddContactButton()
{
    if (!inCall)
    {
        if (ui->AddContactInput->text().isEmpty())
            QMessageBox::information(this, "Error", "No contact name to add");
        else
            this->gui->AddContact(ui->AddContactInput->text().toUtf8().constData());
    }

}

void        MainWindow::UpdateContactList(std::vector<std::pair<std::string, bool>> contactList)
{
    ui->ContactList->model()->removeRows(0, ui->ContactList->model()->rowCount());

    for (std::vector<std::pair<std::string, bool>>::iterator it = contactList.begin(); it != contactList.end(); it++){
        std::pair<std::string, bool> current = *it;
        MyContactListItem *itm = new MyContactListItem(tr(current.first.c_str()));
        if (current.second)
        {
            itm->setIcon(QIcon("ressources/online.png"));
            itm->setOnline(true);
        }
        else
        {
            itm->setIcon(QIcon("ressources/offline.png"));
            itm->setOnline(false);
        }
        ui->ContactList->addItem(itm);
    }
    if (ui->ContactList->count() > 0)
        ui->RemoveContactButton->setDisabled(false);
}

void    MainWindow::updateContact(const std::pair<std::string, bool> &contact)
{
    MyContactListItem *item = nullptr;
    item = static_cast<MyContactListItem *>(ui->ContactList->findItems(contact.first.c_str(), Qt::MatchExactly).at(0));
    if (item == nullptr)
    {
        //May be create contact here ? Don't know ...
        return;
    }
    if (contact.second)
      {

         item->setIcon(QIcon("ressources/online.png"));
         item->setOnline(true);
      }
    else
      {
         item->setIcon(QIcon("ressources/offline.png"));
         item->setOnline(false);
      }
}

void        MainWindow::callButton()
{
    gui->call(ui->ContactNameLabel->text().toUtf8().constData());
    ui->CallButton->setDisabled(true);
    ui->EndCallButton->setDisabled(false);
    ui->callStatus->setText("Calling...");
    this->inCall = true;
}

void    MainWindow::endCallButton()
{
    ui->CallButton->setDisabled(false);
    ui->EndCallButton->setDisabled(true);
    ui->callStatus->setText("");
    this->inCall = false;
}

void    MainWindow::selectContact()
{
    if (!inCall)
    {
        QString contact = ui->ContactList->currentItem()->text();

        if (static_cast<MyContactListItem *>(ui->ContactList->currentItem())->getOnline())
        {
            ui->ContactNameLabel->setText(contact);
            ui->CallButton->setDisabled(false);
        }
        else
        {
            ui->ContactNameLabel->setText(contact + " (Offline)");
            ui->CallButton->setDisabled(true);
        }
        ui->RemoveContactButton->setDisabled(false);
    }
}

void    MainWindow::removeContactButton()
{
    if (!inCall && ui->ContactList->count() > 0 && ui->ContactList->currentItem())
    {
        std::string contact = ui->ContactList->currentItem()->text().toUtf8().constData();
        ui->ContactNameLabel->setText(QString("No contact selected"));
        ui->ContactList->clearSelection();
        this->gui->removeContact(contact);
        if (ui->ContactList->count() <= 0)
            ui->RemoveContactButton->setDisabled(true);
    }
}

void    MainWindow::setInCall(bool inCall)
{
    this->inCall = inCall;
}

void    MainWindow::newError(const std::string &error)
{
    QMessageBox::information(this, "Error", error.c_str());
}

bool    MainWindow::incommingCall(const std::string &userName)
{
     QMessageBox::StandardButton reply;
     (void)userName;
     reply = QMessageBox::question(this, "Incomming Call", "Accept call from ?",
                                    QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes)
     {
         this->setInCall(true);
         return true;
     }
     else
         return false;
}
