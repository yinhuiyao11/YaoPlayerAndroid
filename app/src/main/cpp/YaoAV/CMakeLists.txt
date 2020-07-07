cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

add_library( # Sets the name of the library.
		YaoAV

		# Provides a relative path to your source file(s).
		YaoAVReader.cpp
		YaoAVPacket.cpp
		YaoAVDecode.cpp
		YaoAVStream.cpp
		YaoAVFrame.cpp
		YaoTime.cpp
		)

find_library(
		log-lib

		log
        )

target_link_libraries(
		YaoAV
		${log-lib}
		)





