QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babel
TEMPLATE = app
CONFIG += c++11

LIBS += -lportaudio

LIBS += \
       -lopus

CMAKE_INCLUDE_CURRENT_DIR = ON
CMAKE_AUTOMOC = ON

INCLUDEPATH += includes

SOURCES += sources/client/core/main.cpp \
  sources/client/core/client.cpp \
  sources/client/gui/gui.cpp \
  sources/client/gui/mainwindow.cpp \
  sources/client/gui/mycontactlistitem.cpp \
  sources/client/network/TCPClient.cpp \
  sources/client/sound/Codec.cpp \
  sources/client/sound/SoundControler.cpp \
  sources/client/protocol/Protocol.cpp

HEADERS += includes/ACodec.hh \
           includes/data.h \
           includes/TCPClient.hpp \
           includes/ASoundControler.hh \
           includes/gui.hh \
           includes/client.hpp \
           includes/INetwork.hpp \
           includes/SoundControler.hh \
           includes/Codec.hh \
           includes/mainwindow.h \
           includes/mycontactlistitem.h \
           includes/SoundProperties.hh  \
           includes/Protocol.hpp


FORMS    += \
    sources/client/gui/mainwindow.ui

