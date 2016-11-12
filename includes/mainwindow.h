#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <QMainWindow>
#include <QPushButton>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QListWidget>

#ifdef _MSC_VER
#pragma warning(pop)
#endif


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
    void        updateContact(const std::pair<std::string, bool> &contact);
    void        affInfoMessage(std::string const & msg);
    void        askNetworkInfo();
    const std::pair<std::string, int> &getNetworkInfo() const;
private:
    Gui                 *gui;
    Ui::MainWindow      *ui;
    bool                inCall;
    std::pair<std::string, int> netWorkInfo;
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
