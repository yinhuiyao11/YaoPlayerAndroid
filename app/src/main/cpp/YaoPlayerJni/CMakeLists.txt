cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

include_directories (../)
include_directories (${distribution_DIR}/include)

add_library(
        YaoPlayerJni
        SHARED
        playerJniPlay.cpp

        playerJniUtil.cpp
        JavaVMObj.cpp
)

target_link_libraries(
        YaoPlayerJni

        YaoAV
        YaoGL
        YaoSL
        YaoPlayer
        YaoThread
        EyerCore

        android
        EGL
        GLESv3
        OpenSLES

        ${distribution_DIR}/lib/libavformat.a
        ${distribution_DIR}/lib/libavcodec.a
        ${distribution_DIR}/lib/libswresample.a
        #[[${distribution_DIR}/lib/libswscale.a
        ${distribution_DIR}/lib/libpostproc.a]]
        ${distribution_DIR}/lib/libavutil.a

        ${log-lib}
        z
)



