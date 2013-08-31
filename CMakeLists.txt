cmake_minimum_required (VERSION 2.6)

project(vpx++)

set(CMAKE_DEBUG_POSTFIX -d)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Release)
set(BUILD_SHARED_LIBS ON)

add_library(vpx++_common vpx++.cpp vpx++.h vpx++_exception.h)
add_library(vpx++_encoder vpx++_encoder.cpp vpx++_encoder.h)
add_library(vpx++_decoder vpx++_decoder.cpp vpx++_decoder.h)

set_target_properties(vpx++_common PROPERTIES PUBLIC_HEADER
			"vpx++.h;vpx++_exception.h")
set_target_properties(vpx++_encoder PROPERTIES PUBLIC_HEADER vpx++_encoder.h)
set_target_properties(vpx++_decoder PROPERTIES PUBLIC_HEADER vpx++_decoder.h)

install(TARGETS vpx++_common vpx++_encoder vpx++_decoder
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include)

