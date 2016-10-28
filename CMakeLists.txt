cmake_minimum_required(VERSION 3.4)
project(cpp_babel)

set(CLIENT_NAME "clientBabel")
set(SERVER_NAME "serverBabel")

set(CLIENT_SRCDIR "sources/client/")
set(SERVER_SRCDIR "sources/server/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(includes)

set(CLIENT_SOURCE_FILES
    ${CLIENT_SRCDIR}core/client.cpp
    ${CLIENT_SRCDIR}core/main.cpp)

set(SERVER_SOURCE_FILES
    ${SERVER_SRCDIR}core/main.cpp
    ${SERVER_SRCDIR}core/server.cpp)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
elseif(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

add_executable(${CLIENT_NAME} ${CLIENT_SOURCE_FILES})
add_executable(${SERVER_NAME} ${SERVER_SOURCE_FILES})
