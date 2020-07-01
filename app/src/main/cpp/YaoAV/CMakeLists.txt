
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

include_directories(../3rdpart/ffmpeg-4.1.3/include)

add_library(
	YaoAV
	YaoAVReader.cpp
	YaoAVPacket.cpp
	YaoAVDecode.cpp
	YaoAVStream.cpp
	YaoAVFrame.cpp
	YaoTime.cpp
)




