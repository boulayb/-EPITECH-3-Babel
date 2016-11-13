/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *Stack;
    QWidget *LoginPage;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLineEdit *UsernameLogInput;
    QLabel *label_2;
    QLineEdit *PasswordLogInput;
    QLabel *ErrorLogin;
    QSpacerItem *verticalSpacer;
    QPushButton *loginButton;
    QPushButton *RegisterButton;
    QWidget *RegisterPage;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLineEdit *UsernameRegisterInput;
    QLabel *label_6;
    QLineEdit *PasswordRegisterFirstInput;
    QLabel *label_7;
    QLineEdit *PasswordRegisterSecInput;
    QSpacerItem *verticalSpacer_2;
    QPushButton *RegisterRegisterButton;
    QPushButton *CancelRegisterButton;
    QWidget *LoggedPage;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *ContactNameLabel;
    QLabel *callStatus;
    QPushButton *CallButton;
    QPushButton *EndCallButton;
    QPushButton *RemoveContactButton;
    QLabel *LoginLabel;
    QLineEdit *AddContactInput;
    QPushButton *LogoutButton;
    QPushButton *AddContactButton;
    QListWidget *ContactList;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(660, 491);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Stack = new QStackedWidget(centralWidget);
        Stack->setObjectName(QString::fromUtf8("Stack"));
        LoginPage = new QWidget();
        LoginPage->setObjectName(QString::fromUtf8("LoginPage"));
        gridLayout_2 = new QGridLayout(LoginPage);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(LoginPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        UsernameLogInput = new QLineEdit(LoginPage);
        UsernameLogInput->setObjectName(QString::fromUtf8("UsernameLogInput"));
        UsernameLogInput->setAutoFillBackground(true);

        verticalLayout_2->addWidget(UsernameLogInput);

        label_2 = new QLabel(LoginPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        PasswordLogInput = new QLineEdit(LoginPage);
        PasswordLogInput->setObjectName(QString::fromUtf8("PasswordLogInput"));
        PasswordLogInput->setAutoFillBackground(true);
        PasswordLogInput->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(PasswordLogInput);

        ErrorLogin = new QLabel(LoginPage);
        ErrorLogin->setObjectName(QString::fromUtf8("ErrorLogin"));
        ErrorLogin->setEnabled(true);
        ErrorLogin->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(ErrorLogin);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        loginButton = new QPushButton(LoginPage);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        verticalLayout_2->addWidget(loginButton);

        RegisterButton = new QPushButton(LoginPage);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));

        verticalLayout_2->addWidget(RegisterButton);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        Stack->addWidget(LoginPage);
        RegisterPage = new QWidget();
        RegisterPage->setObjectName(QString::fromUtf8("RegisterPage"));
        gridLayout_4 = new QGridLayout(RegisterPage);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(RegisterPage);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_5);

        UsernameRegisterInput = new QLineEdit(RegisterPage);
        UsernameRegisterInput->setObjectName(QString::fromUtf8("UsernameRegisterInput"));
        UsernameRegisterInput->setAutoFillBackground(true);

        verticalLayout_3->addWidget(UsernameRegisterInput);

        label_6 = new QLabel(RegisterPage);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        PasswordRegisterFirstInput = new QLineEdit(RegisterPage);
        PasswordRegisterFirstInput->setObjectName(QString::fromUtf8("PasswordRegisterFirstInput"));
        PasswordRegisterFirstInput->setAutoFillBackground(true);
        PasswordRegisterFirstInput->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(PasswordRegisterFirstInput);

        label_7 = new QLabel(RegisterPage);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_7);

        PasswordRegisterSecInput = new QLineEdit(RegisterPage);
        PasswordRegisterSecInput->setObjectName(QString::fromUtf8("PasswordRegisterSecInput"));
        PasswordRegisterSecInput->setAutoFillBackground(true);
        PasswordRegisterSecInput->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(PasswordRegisterSecInput);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        RegisterRegisterButton = new QPushButton(RegisterPage);
        RegisterRegisterButton->setObjectName(QString::fromUtf8("RegisterRegisterButton"));

        verticalLayout_3->addWidget(RegisterRegisterButton);

        CancelRegisterButton = new QPushButton(RegisterPage);
        CancelRegisterButton->setObjectName(QString::fromUtf8("CancelRegisterButton"));

        verticalLayout_3->addWidget(CancelRegisterButton);


        gridLayout_4->addLayout(verticalLayout_3, 0, 0, 1, 1);

        Stack->addWidget(RegisterPage);
        LoggedPage = new QWidget();
        LoggedPage->setObjectName(QString::fromUtf8("LoggedPage"));
        verticalLayout_4 = new QVBoxLayout(LoggedPage);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ContactNameLabel = new QLabel(LoggedPage);
        ContactNameLabel->setObjectName(QString::fromUtf8("ContactNameLabel"));
        ContactNameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(ContactNameLabel);

        callStatus = new QLabel(LoggedPage);
        callStatus->setObjectName(QString::fromUtf8("callStatus"));
        callStatus->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(callStatus);

        CallButton = new QPushButton(LoggedPage);
        CallButton->setObjectName(QString::fromUtf8("CallButton"));
        CallButton->setEnabled(false);

        verticalLayout->addWidget(CallButton);

        EndCallButton = new QPushButton(LoggedPage);
        EndCallButton->setObjectName(QString::fromUtf8("EndCallButton"));
        EndCallButton->setEnabled(false);

        verticalLayout->addWidget(EndCallButton);

        RemoveContactButton = new QPushButton(LoggedPage);
        RemoveContactButton->setObjectName(QString::fromUtf8("RemoveContactButton"));
        RemoveContactButton->setEnabled(false);

        verticalLayout->addWidget(RemoveContactButton);


        gridLayout_3->addLayout(verticalLayout, 5, 1, 1, 1);

        LoginLabel = new QLabel(LoggedPage);
        LoginLabel->setObjectName(QString::fromUtf8("LoginLabel"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        LoginLabel->setFont(font);
        LoginLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(LoginLabel, 0, 0, 1, 1);

        AddContactInput = new QLineEdit(LoggedPage);
        AddContactInput->setObjectName(QString::fromUtf8("AddContactInput"));
        AddContactInput->setAutoFillBackground(true);

        gridLayout_3->addWidget(AddContactInput, 1, 0, 1, 1);

        LogoutButton = new QPushButton(LoggedPage);
        LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));

        gridLayout_3->addWidget(LogoutButton, 0, 1, 1, 1);

        AddContactButton = new QPushButton(LoggedPage);
        AddContactButton->setObjectName(QString::fromUtf8("AddContactButton"));

        gridLayout_3->addWidget(AddContactButton, 2, 0, 1, 1);

        ContactList = new QListWidget(LoggedPage);
        ContactList->setObjectName(QString::fromUtf8("ContactList"));

        gridLayout_3->addWidget(ContactList, 5, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);

        Stack->addWidget(LoggedPage);

        gridLayout->addWidget(Stack, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        Stack->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Babel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        ErrorLogin->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0000;\">Wrong Username and Password combo</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        loginButton->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        RegisterButton->setText(QApplication::translate("MainWindow", "Register", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Repeat password", 0, QApplication::UnicodeUTF8));
        RegisterRegisterButton->setText(QApplication::translate("MainWindow", "Register", 0, QApplication::UnicodeUTF8));
        CancelRegisterButton->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        ContactNameLabel->setText(QApplication::translate("MainWindow", "Contact Name", 0, QApplication::UnicodeUTF8));
        callStatus->setText(QString());
        CallButton->setText(QApplication::translate("MainWindow", "Call", 0, QApplication::UnicodeUTF8));
        EndCallButton->setText(QApplication::translate("MainWindow", "Endcall", 0, QApplication::UnicodeUTF8));
        RemoveContactButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        LoginLabel->setText(QApplication::translate("MainWindow", "login", 0, QApplication::UnicodeUTF8));
        AddContactInput->setPlaceholderText(QApplication::translate("MainWindow", "Find a contact ..", 0, QApplication::UnicodeUTF8));
        LogoutButton->setText(QApplication::translate("MainWindow", "Logout", 0, QApplication::UnicodeUTF8));
        AddContactButton->setText(QApplication::translate("MainWindow", "Add contact", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
