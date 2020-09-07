cmake_minimum_required(VERSION 3.4.1)

##官方标准配置
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

add_library(
	YaoAV
	YaoAVReader.cpp
	YaoAVPacket.cpp
	YaoAVDecode.cpp
	YaoAVStream.cpp
	YaoAVFrame.cpp
	YaoTime.cpp
		EyerAVBitstreamFilter.cpp
)

target_link_libraries(
		YaoAV

		${distribution_DIR}/lib/libavformat.a
		${distribution_DIR}/lib/libavcodec.a
		${distribution_DIR}/lib/libswresample.a
		#[[${distribution_DIR}/lib/libswscale.a
        ${distribution_DIR}/lib/libpostproc.a]]
		${distribution_DIR}/lib/libavutil.a

		${log-lib}
		z
)

find_library(
		log-lib

		log
)

target_link_libraries(
		YaoAV
		${log-lib}
)




