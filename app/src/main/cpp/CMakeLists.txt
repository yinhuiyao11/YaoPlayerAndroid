cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

set(distribution_DIR ${CMAKE_SOURCE_DIR}/../jniLibs/armeabi-v7a/ffmpeg_install)

include_directories (../)
include_directories (./)
include_directories (${distribution_DIR}/include)

ADD_DEFINITIONS(-D EYER_PLATFORM_ANDROID)

ADD_SUBDIRECTORY(YaoAV)
ADD_SUBDIRECTORY(YaoGL)
ADD_SUBDIRECTORY(YaoPlayer)
ADD_SUBDIRECTORY(YaoThread)
ADD_SUBDIRECTORY(YaoPlayerJni)
ADD_SUBDIRECTORY(EyerCore)
ADD_SUBDIRECTORY(YaoSL)


