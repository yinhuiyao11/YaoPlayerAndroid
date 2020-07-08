cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

set(distribution_DIR ${CMAKE_SOURCE_DIR}/../jniLibs/armeabi-v7a/ffmpeg_install)

include_directories (../)
include_directories (./)
include_directories (${distribution_DIR}/include)

ADD_SUBDIRECTORY(YaoAV)
ADD_SUBDIRECTORY(YaoGL)
ADD_SUBDIRECTORY(YaoPlayer)
ADD_SUBDIRECTORY(YaoThread)
ADD_SUBDIRECTORY(YaoPlayerJni)

add_library(
        native-lib

        SHARED

        native-lib.cpp
        )

find_library(
        log-lib
        log
        )

target_link_libraries(
        native-lib

        YaoAV
        YaoGL
        YaoPlayerJni

        android
        EGL
        GLESv3

        ${distribution_DIR}/lib/libavformat.a
        ${distribution_DIR}/lib/libavcodec.a
        ${distribution_DIR}/lib/libswresample.a
        #[[${distribution_DIR}/lib/libswscale.a
        ${distribution_DIR}/lib/libpostproc.a]]
        ${distribution_DIR}/lib/libavutil.a

        ${log-lib}
        z
        )
