cmake_minimum_required(VERSION 3.4)
project(DeProfundis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES
        src/main_cube.cpp
        src/ShaderProgram.cpp src/ShaderProgram.hpp
        src/ProgramArguments.cpp src/ProgramArguments.hpp
        src/GLFWControls.cpp src/GLFWControls.hpp
        src/OpenGL.hpp)

add_executable(DeProfundisCMAKE ${SOURCE_FILES})

add_custom_target(DeProfundis ALL COMMAND mingw32-make all WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(DeProfundisDEBUG ALL COMMAND mingw32-make all DEBUG=-g WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})