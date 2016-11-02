#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T11:59:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gui.cpp \
    mycontactlistitem.cpp

HEADERS  += mainwindow.h \
         data.h \
    gui.hh \
    mycontactlistitem.h

FORMS    += \
    mainwindow.ui

