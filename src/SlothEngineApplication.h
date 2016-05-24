#ifndef SLOTHENGINE_SLOTHENGINEAPPLICATION_H
#define SLOTHENGINE_SLOTHENGINEAPPLICATION_H

#include <string>
#include <iostream>
#include "OpenGL.hpp"
#include "ShaderProgramCreator.h"
#include "SlothEngineProgramSample.h"
#include "InputProcessor.h"

class SlothEngineApplication {
public:
   GLFWwindow *window;
   int windowsWidth;
   int windowsHeight;

   bool shouldPrintFPS = true;

   static SlothEngineApplication &get();

   static SlothEngineApplication &create(SlothEngineProgramSample *slothEngineProgram);

   void start();

private:
   SlothEngineApplication() { };
   InputProcessor *inputProcessor;
   SlothEngineProgramSample *slothEngineProgram;
   PhongShader *phongShader;
   static float deltaTime;
   static float lastFrameTime;

   int framesSinceLastFPS;
   float lastCounterTime;

   void initialize();
   void initializeShaders();

   void calculateDeltaTime();
   void setInputMode();

   void showFPS();

   void printOpenGLInfo();

   void getConfiguration(int &win_width, int &win_height, std::string &win_name);

   static void error_callback(int error, const char *description) {
      std::cerr << "Error code: " << error << " ; Description: " << description << std::endl;
   }
};


#endif //SLOTHENGINE_SLOTHENGINEAPPLICATION_H
