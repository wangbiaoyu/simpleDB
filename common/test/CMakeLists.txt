cmake_minimum_required(VERSION 3.2)
#project(test)

#set(CXX_FLAGS
#   -g
#    -Wall
#    -std=c++11
#    -D_PTHREADS
#    -Wno-unused-parameter
#)


#set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SRC
	${CMAKE_CURRENT_LIST_DIR}/../log.cc
	${CMAKE_CURRENT_LIST_DIR}/log_test.cc
	)

add_compile_options("-g")

add_executable(log_test ${SRC})

target_link_libraries(log_test pthread rt)

