#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QListWidget>
#include <QDialogButtonBox>
#include <QFormLayout>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui.hh"
#include <iostream>
#include "mycontactlistitem.h"

MainWindow::MainWindow(Gui *gui, QWidget *parent) : QMainWindow(parent), gui(gui), ui(new Ui::MainWindow), netWorkInfo("127.0.0.1", 4000)
{
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
        QByteArray password = QCryptographicHash::hash(ui->PasswordLogInput->text().toUtf8(),QCryptographicHash::Md5);
        QString passwordHash(password.toHex());

        std::cout << "Test" << std::endl;
        this->gui->askLogin(ui->UsernameLogInput->text().toUtf8().constData(), passwordHash.toUtf8().constData());
      std::cout << "Test2" << std::endl;
        this->ui->LoginLabel->setText(ui->UsernameLogInput->text());
    }
}

void        MainWindow::Login()
{
    ui->Stack->setCurrentIndex(2);
}

void        MainWindow::askNetworkInfo()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

// Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    lineEdit->setText("127.0.0.1");
    QString label = QString("Server IP");
    form.addRow(label, lineEdit);
    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setText("4000");
    QString label2 = QString("Server port");
    form.addRow(label2, lineEdit2);
    fields << lineEdit;
    fields << lineEdit2;


// Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

// Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        this->netWorkInfo.first = fields.takeFirst()->text().toStdString();
        this->netWorkInfo.second = fields.takeLast()->text().toInt();
    }
    else
        exit(0);
}

const std::pair<std::string, int> &MainWindow::getNetworkInfo() const
{
  return this->netWorkInfo;
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
        QByteArray password = QCryptographicHash::hash(ui->PasswordRegisterFirstInput->text().toUtf8(),QCryptographicHash::Md5);
        QString passwordHash(password.toHex());

        this->gui->askRegister(ui->UsernameRegisterInput->text().toUtf8().constData(), passwordHash.toUtf8().constData());
    }
}

void        MainWindow::RegisterButton()
{
    ui->Stack->setCurrentIndex(1);
}

void        MainWindow::CancelRegisterButton()
{
    ui->Stack->setCurrentIndex(0);
}

void        MainWindow::LogoutButton()
{
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
    if (ui->AddContactInput->text().isEmpty())
        QMessageBox::information(this, "Error", "No contact name to add");
    else
        this->gui->AddContact(ui->AddContactInput->text().toUtf8().constData());
}

void        MainWindow::UpdateContactList(std::vector<std::pair<std::string, bool>> contactList)
{
    ui->ContactList->clear();
//    ui->ContactList->model()->removeRows(0, ui->ContactList->model()->rowCount());

    for (std::vector<std::pair<std::string, bool>>::iterator it = contactList.begin(); it != contactList.end(); it++)
    {
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
         if (ui->ContactList->currentItem()->text() == contact.first.c_str())
            {
                ui->ContactNameLabel->setText(contact.first.c_str());
                ui->CallButton->setDisabled(false);
            }
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
    this->setInCallView("Calling...");
}

void    MainWindow::endCallButton()
{
    this->setContactView();
    this->gui->endCall();
}

void    MainWindow::selectContact()
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

void    MainWindow::removeContactButton()
{
    if (ui->ContactList->count() > 0 && ui->ContactList->currentItem())
    {
        std::string contact = ui->ContactList->currentItem()->text().toUtf8().constData();
        ui->ContactNameLabel->setText(QString("No contact selected"));
        ui->ContactList->clearSelection();
        this->gui->removeContact(contact);
        if (ui->ContactList->count() <= 0)
            ui->RemoveContactButton->setDisabled(true);
    }
}

void        MainWindow::setContactView()
{
    ui->ContactList->setDisabled(false);
    ui->EndCallButton->setDisabled(true);
    ui->LogoutButton->setDisabled(false);
    ui->RemoveContactButton->setDisabled(false);
    ui->CallButton->setDisabled(false);
    ui->callStatus->setText("");
}

void    MainWindow::setInCallView(std::string const &name)
{
    ui->ContactList->setDisabled(true);
    ui->EndCallButton->setDisabled(false);
    ui->LogoutButton->setDisabled(true);
    ui->RemoveContactButton->setDisabled(true);
    ui->CallButton->setDisabled(true);
    ui->callStatus->setText(QString(name.c_str()));
}

void    MainWindow::newError(const std::string &error)
{
    QMessageBox::information(this, "Error", error.c_str());
}

bool    MainWindow::incommingCall(const std::string &userName)
{
     QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Incoming Call", "Accept call from ?",
                                    QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes)
     {
       std::string data = "In call with " + userName;
       this->setInCallView(data);
       return true;
     }
     else
         return false;
}
