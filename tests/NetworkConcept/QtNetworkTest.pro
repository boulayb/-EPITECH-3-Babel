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

SOURCES += mainClient.cpp \
    src/Session.cpp \
    src/TCPClient.cpp \
    src/TCPServer.cpp \
    src/UDPClient.cpp \
    src/TaskManager.cpp \
    src/Server.cpp

INCLUDEPATH += includes

HEADERS += \
    includes/INetwork.hpp \
    includes/Protocol.hpp \
    includes/Session.hpp \
    includes/TCPClient.hpp \
    includes/TCPServer.hpp \
    includes/UDPClient.hpp \
    includes/ThreadPool.hpp \
    includes/TaskManager.hpp \
    includes/Server.hpp

