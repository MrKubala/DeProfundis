#include "SlothEngineApplication.h"

SlothEngineApplication &SlothEngineApplication::get() {
   static SlothEngineApplication slothEngineApplication;
   return slothEngineApplication;
}

SlothEngineApplication &SlothEngineApplication::create(SlothEngineProgramSample &slothEngineProgram) {
   SlothEngineApplication &slothEngineApplication = SlothEngineApplication::get();
   slothEngineApplication.slothEngineProgram = slothEngineProgram;
   slothEngineApplication.inputProcessor = InputProcessor::getInputProcessor();
   return slothEngineApplication;
}

void SlothEngineApplication::start() {
   initialization();

   while (!glfwWindowShouldClose(window)) {
      glEnableVertexAttribArray(0);
      calculateDeltaTime();
      showFPS();
      inputProcessor->update();


      shaderProgram.use();
      glViewport(0, 0, windowsWidth, windowsHeight);
      slothEngineProgram.render(deltaTime);
      glfwSwapBuffers(window);

   }

   glfwTerminate();
   exit(EXIT_SUCCESS);
}

void SlothEngineApplication::initialization() {
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
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   shaderProgram.addShaderFromFile(GL_VERTEX_SHADER, "./../shaders/vertexShader.glsl");
   shaderProgram.addShaderFromFile(GL_FRAGMENT_SHADER, "./../shaders/fragmentShader.glsl");
   shaderProgram.link();
   Sloth::shaderProgram = &shaderProgram;

   slothEngineProgram.create();

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
}

void SlothEngineApplication::calculateDeltaTime() {
   deltaTime = (float) glfwGetTime() - lastFrameTime;
   lastFrameTime += deltaTime;
}

float SlothEngineApplication::deltaTime = 0;
float SlothEngineApplication::lastFrameTime = 0;

void SlothEngineApplication::showFPS() {
   if (shouldPrintFPS) {
      framesSinceLastFPS++;
      double currentTime = glfwGetTime();
      if (currentTime - lastFPSCounterTime >= 1.0) {
         printf("%f ms/frame  ||  %d FPS \n", 1000.0 / double(framesSinceLastFPS), framesSinceLastFPS);
         framesSinceLastFPS = 0;
         lastFPSCounterTime = (float) currentTime;
      }
   }
}

