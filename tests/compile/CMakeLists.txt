cmake_minimum_required(VERSION 3.4)
project(babel_test)

set(TEST_NAME "babel_test")

## make sure that boost is dyn linked
# set(Boost_USE_STATIC_LIBS        OFF)
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME     OFF)
# set(BOOST_ALL_DYN_LINK           ON)

set(BOOST_LIBRARYDIR "libs/")

if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
  ## tell where to find boost
  # set(BOOST_ROOT "/usr/include/boost/")
  # set(BOOST_LIBRARYDIR "/usr/lib64/")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## components needed from boost
find_package(Boost 1.47 COMPONENTS system REQUIRED)

include_directories(.)

set(TEST_SOURCE_FILES
    test.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
