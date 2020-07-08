cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

include_directories (../)
include_directories (${distribution_DIR}/include)

add_library(
        YaoPlayerJni
        SHARED
        playerJniGL.cpp
)

target_link_libraries(
        YaoPlayerJni

        YaoAV
        YaoGL

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



