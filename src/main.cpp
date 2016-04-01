#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
   // When a user presses the escape key, we set the WindowShouldClose property to true,
   // closing the application
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
}

int width = 960;
int height = 540;

int main() {
   ///// GLFW stuff /////
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   GLFWwindow *window = glfwCreateWindow(width, height, "DeProfundis", nullptr, nullptr);
   if (window == nullptr) {
      std::cout << "Failed to createGLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);

   ///// GLEW stuff /////
   glewExperimental = GL_TRUE;
   if (glewInit() != GLEW_OK) {
      std::cout << "Failed to initialize GLEW" << std::endl;
   }

   glViewport(0, 0, width, height);

   glfwSetKeyCallback(window, key_callback);

   //SHADERS
   Shader shader("asdf");

   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);


      GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f
      };

      GLuint VBO;
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glfwSwapBuffers(window);
   }

   glfwTerminate();

   return 0;
}
