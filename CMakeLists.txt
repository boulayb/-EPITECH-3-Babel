cmake_minimum_required(VERSION 3.4)
project(cpp_babel)

option(BUILD_CLIENT "Build Client" ON)
option(BUILD_SERVER "Build Server" ON)

## AUTOMOC for QT UI Files
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CLIENT_NAME "clientBabel")
set(SERVER_NAME "serverBabel")

set(CLIENT_SRCDIR "sources/client/")
set(SERVER_SRCDIR "sources/server/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(INC_DIR "includes" "libs/include/")

set(CLIENT_SOURCE_FILES
  ${CLIENT_SRCDIR}core/main.cpp
  ${CLIENT_SRCDIR}core/client.cpp
  ${CLIENT_SRCDIR}gui/gui.cpp
  ${CLIENT_SRCDIR}gui/mainwindow.cpp
  ${CLIENT_SRCDIR}gui/mycontactlistitem.cpp
  ${CLIENT_SRCDIR}network/ANetwork.cpp
  ${CLIENT_SRCDIR}network/TCPClient.cpp
  ${CLIENT_SRCDIR}network/UDPClient.cpp
  ${CLIENT_SRCDIR}sound/Codec.cpp
  ${CLIENT_SRCDIR}sound/SoundControler.cpp
  ${CLIENT_SRCDIR}protocol/Protocol.cpp)

set(SERVER_SOURCE_FILES
  ${SERVER_SRCDIR}core/main.cpp
  ${SERVER_SRCDIR}core/Server.cpp
  ${SERVER_SRCDIR}core/TaskManager.cpp
  ${SERVER_SRCDIR}database/DataBase.cpp
  ${SERVER_SRCDIR}database/User.cpp
  ${SERVER_SRCDIR}network/Session.cpp
  ${SERVER_SRCDIR}network/TCPServer.cpp
  ${SERVER_SRCDIR}protocol/Protocol.cpp)

## libs needed
find_package(Qt4 4.4.3 REQUIRED QtCore QtGui QtNetwork)
find_package(Boost 1.47 COMPONENTS system serialization REQUIRED)

## make sure that boost is dyn linked
set(Boost_USE_STATIC_LIBS OFF CACHE BOOL "use static libraries from Boost")
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ALL_DYN_LINK ON)

## QT MOC precompilation
set(UI_FILE ${CLIENT_SRCDIR}gui/mainwindow.ui)
set(MOC_CPP ${CLIENT_SRCDIR}gui/mainwindow.cpp ${CLIENT_SRCDIR}network/TCPClient.cpp ${CLIENT_SRCDIR}network/UDPClient.cpp)
set(MOC_INC includes/mainwindow.h includes/TCPClient.hpp includes/UDPClient.hpp)
QT4_WRAP_CPP(MOC_SRC ${MOC_INC} ${MOC_CPP})
QT4_WRAP_UI(UI_SRC ${UI_FILE})
list(APPEND CLIENT_SOURCE_FILES ${UI_SRC} ${MOC_SRC})

set(CLIENT_LIBS_LINK Qt4::QtCore Qt4::QtGui Qt4::QtNetwork opus)
set(SERVER_LIBS_LINK ${Boost_LIBRARIES})

if(WIN32)
	set(Boost_NO_SYSTEM_PATHS true)
	set(BOOST_ROOT "C:\\boost\\")
	add_definitions( -DBOOST_ALL_NO_LIB )
	add_definitions( -DBOOST_ALL_DYN_LINK )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
	link_directories("libs/windows/")
	set(INC_DIR ${INC_DIR} "C:\\boost\\include\\boost-1_62\\")
	set(CLIENT_LIBS_LINK ${CLIENT_LIBS_LINK} portaudio_x86)
elseif(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g3")
	link_directories("libs/linux/")
	set(CLIENT_LIBS_LINK ${CLIENT_LIBS_LINK} portaudio pthread)
	set(SERVER_LIBS_LINK ${SERVER_LIBS_LINK} pthread)
endif()

include_directories(${INC_DIR})

if(BUILD_CLIENT)
  add_executable(${CLIENT_NAME} ${CLIENT_SOURCE_FILES})
  target_link_libraries(${CLIENT_NAME} ${CLIENT_LIBS_LINK})
endif()

if(BUILD_SERVER)
  add_executable(${SERVER_NAME} ${SERVER_SOURCE_FILES})
  target_link_libraries(${SERVER_NAME} ${SERVER_LIBS_LINK})
endif()
