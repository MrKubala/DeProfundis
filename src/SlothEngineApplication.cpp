#include "SlothEngineApplication.h"

SlothEngineApplication &SlothEngineApplication::get() {
   static SlothEngineApplication slothEngineApplication;
   return slothEngineApplication;
}

SlothEngineApplication &SlothEngineApplication::create(SlothEngineProgramSample &slothEngineProgram) {
   SlothEngineApplication &slothEngineApplication = SlothEngineApplication::get();
   slothEngineApplication.slothEngineProgram = slothEngineProgram;
   slothEngineApplication.inputProcessor = InputProcessor::getInputProcessor();
   Sloth::phongShader = slothEngineApplication.phongShader;
   Sloth::framesPerSecond = &slothEngineApplication.framesSinceLastFPS;
   return slothEngineApplication;
}

void SlothEngineApplication::start() {
   initialize();

   while (!glfwWindowShouldClose(window)) {
      setInputMode();

      calculateDeltaTime();
      showFPS();
      inputProcessor->update();
      glViewport(0, 0, windowsWidth, windowsHeight);
      phongShader->bind();

      slothEngineProgram.render(deltaTime);

      glfwSwapBuffers(window);

   }

   glfwTerminate();
   exit(EXIT_SUCCESS);
}

void SlothEngineApplication::initialize() {
   std::string win_name;

   getConfiguration(windowsWidth, windowsHeight, win_name);

   window = nullptr;

   if (!glfwInit()) {
      exit(EXIT_FAILURE);
   }

   window = glfwCreateWindow(windowsWidth, windowsHeight, win_name.c_str(), NULL, NULL);
   if (!window) {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   glfwMakeContextCurrent(window);
   glfwSwapInterval(0);

   glewExperimental = GL_TRUE;
   glewInit();

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glEnable(GL_CULL_FACE);

   printOpenGLInfo();

   glfwSetErrorCallback(error_callback);
   glfwSetKeyCallback(window, inputProcessor->key_callback);
   glfwSetCursorPosCallback(window, inputProcessor->mouse_position_callback);
   glfwSetMouseButtonCallback(window, inputProcessor->mouse_button_callback);
   glfwSetScrollCallback(window, inputProcessor->mouse_scroll_callback);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

   initializeShaders();

   slothEngineProgram.create();
}

void SlothEngineApplication::initializeShaders() {
   this->phongShader = new PhongShader("./../shaders/vertexShader.glsl", "./../shaders/fragmentShader.glsl");
   Sloth::phongShader = this->phongShader;
}

void SlothEngineApplication::printOpenGLInfo() {
   const GLubyte *renderer = glGetString(GL_RENDERER);
   const GLubyte *version = glGetString(GL_VERSION);
   printf("Renderer: %s\n", renderer);
   printf("OpenGL version supported %s\n", version);
}

void SlothEngineApplication::getConfiguration(int &win_width, int &win_height, std::string &win_name) {
   win_width = 960;
   win_height = 540;
   win_name = "SlothEngineOBJViewer";
   Sloth::windowsWidth = &win_width;
   Sloth::windowsHeight = &win_height;
}

void SlothEngineApplication::calculateDeltaTime() {
   deltaTime = (float) glfwGetTime() - lastFrameTime;
   lastFrameTime += deltaTime;
}

float SlothEngineApplication::deltaTime = 0;
float SlothEngineApplication::lastFrameTime = 0;

void SlothEngineApplication::showFPS() {
   framesSinceLastFPS++;
   double currentTime = glfwGetTime();
   if (currentTime - lastCounterTime >= 1.0) {
      if (shouldPrintFPS)
         printf("%f ms/frame  ||  %d FPS \n", 1000.0 / double(framesSinceLastFPS), framesSinceLastFPS);

      framesSinceLastFPS = 0;
      lastCounterTime = (float) currentTime;
   }

}

void SlothEngineApplication::setInputMode() {
   double currentTime = glfwGetTime();
   if (currentTime - lastCounterTime >= 1.0) {
      if (Sloth::freeMouseMode)glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   }
}



