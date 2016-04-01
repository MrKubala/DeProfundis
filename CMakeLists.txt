cmake_minimum_required(VERSION 3.4)
project(DeProfundis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES
        main.cpp)

add_executable(DeProfundisCMAKE ${SOURCE_FILES})

add_custom_target(DeProfundis ALL COMMAND mingw32-make build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})