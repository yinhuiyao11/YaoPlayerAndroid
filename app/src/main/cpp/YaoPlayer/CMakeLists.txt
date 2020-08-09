cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

include_directories (../)

add_library(
    YaoPlayer

    YaoPlayer.cpp
    YaoPlayerReaderThread.cpp
    YaoDecodeThread.cpp
    YaoPlayerCtr.cpp
    YaoPlayerGL.cpp
)

target_link_libraries(
        YaoPlayer

        YaoAV
        YaoGL
        YaoSL
)
