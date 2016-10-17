QT += core
QT += network
QT -= gui

CMAKE_INCLUDE_CURRENT_DIR = ON
CMAKE_AUTOMOC = ON

CONFIG += c++11

LIBS += \
       -lboost_system\


TARGET = QtNetworkTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    TCPClient.cpp \
    TCPServer.cpp \
    Session.cpp

HEADERS += \
    Protocol.hpp \
    INetwork.hpp \
    TCPClient.hpp \
    TCPServer.hpp \
    Session.hpp

