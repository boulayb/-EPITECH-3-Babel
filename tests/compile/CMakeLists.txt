cmake_minimum_required(VERSION 3.4)
project(babel_test)

set(TEST_NAME "babel_test")

## make sure that boost is dyn linked
set(Boost_USE_STATIC_LIBS OFF CACHE BOOL "use static libraries from Boost")
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ALL_DYN_LINK ON)

if(WIN32)
  set(Boost_NO_SYSTEM_PATHS true)
  set(BOOST_ROOT "C:\\boost\\")
  add_definitions( -DBOOST_ALL_NO_LIB )
  add_definitions( -DBOOST_ALL_DYN_LINK )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
  include_directories(. "C:\\boost\\include\\boost-1_62\\")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
  link_directories(".")
  include_directories(.)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## components needed from boost
find_package(Boost 1.47 COMPONENTS system REQUIRED)

set(TEST_SOURCE_FILES
    test.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
