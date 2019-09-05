cmake_minimum_required(VERSION 3.2)
project(common LANGUAGES CXX)

add_library(${PROJECT_NAME} PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/mutex.h
		${CMAKE_CURRENT_LIST_DIR}/thread.h
		${CMAKE_CURRENT_LIST_DIR}/log.h
		${CMAKE_CURRENT_LIST_DIR}/util.h

		${CMAKE_CURRENT_LIST_DIR}/log.cc
		)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(test)
