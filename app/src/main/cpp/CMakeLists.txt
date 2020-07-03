# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(distribution_DIR ${CMAKE_SOURCE_DIR}/../jniLibs/armeabi-v7a/ffmpeg_install)

include_directories (${distribution_DIR}/include)

add_library( avutil
        STATIC
        IMPORTED )
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libavutil.a)

add_library( avcodec
        STATIC
        IMPORTED )
set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libavcodec.a)

add_library( avfilter
        STATIC
        IMPORTED )
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libavfilter.a)

add_library( avformat
        STATIC
        IMPORTED )
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libavformat.a)

add_library( postproc
        STATIC
        IMPORTED )
set_target_properties( postproc
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libpostproc.a)

add_library( swresample
        STATIC
        IMPORTED )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libswresample.a)

add_library( swscale
        STATIC
        IMPORTED )
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libswscale.a)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp
             gl/YaoGLProgram.cpp
             gl/YaoGLShader.cpp
             gl/YaoVAO.cpp
             gl/YaoGLTexture.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       android
                       EGL
                       GLESv3

                       avutil
                       avcodec
                       avfilter
                       avformat
                       postproc
                       swresample
                       swscale

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )