cmake_minimum_required(VERSION 2.6)
project(Babel)

if (UNIX)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      # set (CMAKE_CXX_FLAGS "--std=gnu++11 -W -Wall -Werror -Wextra -g ${CMAKE_CXX_FLAGS}")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 -g ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
    
  include_directories(
    include
    lib/include
    )

  link_directories(
    lib/linux
    )
  add_executable(
    babel
    src/main.cpp
    src/SoundControler.cpp
    src/Codec.cpp
    )

  target_link_libraries(
    babel
    asound
    c
    db-5.3
    dl
    gcc_s
    jack
    m
    opus
    portaudio
    pthread
    rt
    stdc++
    )
endif(UNIX)


if (WIN32)
  set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
  
  include_directories(
    include
    lib/include
    )
  
  link_directories(
    lib/win
    )
    
  add_executable(
    babel
    src/main.cpp
    src/SoundControler.cpp
    src/Codec.cpp
    )

  target_link_libraries(
    opus
    portaudio_x86
    )
 
endif (WIN32)
