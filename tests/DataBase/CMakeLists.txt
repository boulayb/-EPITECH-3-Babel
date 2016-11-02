cmake_minimum_required(VERSION 3.4)
project(BabelCE)
include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/DataBase.cpp include/DataBase.h include/Protocol.h include/User.h src/User.cpp)
add_executable(BabelCE ${SOURCE_FILES})
target_link_libraries(BabelCE
        -lboost_program_options -lboost_filesystem -lboost_system -lboost_serialization)
