cmake_minimum_required(VERSION 3.4)
project(SlothEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)
link_directories(lib)
link_libraries(SOIL glfw3dll glew32 glew32.dll opengl32)

set(SOURCE_FILES
        src/SlothEngineApplication.cpp src/SlothEngineApplication.h
        src/ShaderProgram.cpp src/ShaderProgram.h
        src/OpenGL.hpp
        src/Texture.cpp src/Texture.h
        src/Camera.cpp src/Camera.h
        src/InputProcessor.cpp src/InputProcessor.h
        src/Mesh.cpp src/Mesh.h
        src/SlothEngineProgramSample.cpp
        src/SlothEngineProgramSample.h src/SlothEngineSample.cpp
        src/GameObject.cpp src/GameObject.h src/Sloth.cpp src/Sloth.h)

add_executable(${PROJECT_NAME}CMAKE ${SOURCE_FILES})