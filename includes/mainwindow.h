#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class Gui;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit    MainWindow(Gui *gui, QWidget *parent = 0);
    ~MainWindow();

    void        UpdateContactList(std::vector<std::pair<std::string, bool>> contactList);
    void        setInCall(bool inCall);
    void        newError(const std::string &error);
    void        Login();
    void        setLoginView();
    bool        incommingCall(const std::string &userName);
    void        updateContact(std::pair<std::string, bool> contact);
    void        affInfoMessage(std::string const & msg);

private:
    Ui::MainWindow      *ui;
    QCryptographicHash  *hash;
    Gui                 *gui;
    bool                inCall;

private slots:
    void    LoginButton();
    void    RegisterButton();
    void    CancelRegisterButton();
    void    LogoutButton();
    void    RegisterRegisterButton();
    void    AddContactButton();
    void    callButton();
    void    endCallButton();
    void    selectContact();
    void    removeContactButton();
};

#endif // MAINWINDOW_H
