#include <iostream>
#include <random>
#include "ProgramArguments.hpp"
#include "GLFWControls.hpp"
#include "ShaderProgram.h"
#include "Texture.h"
#include "InputProcessor.h"
#include "Camera.h"
#include "Mesh.h"

void printOpenGLInfo() {
   const GLubyte *renderer = glGetString(GL_RENDERER);
   const GLubyte *version = glGetString(GL_VERSION);
   printf("Renderer: %s\n", renderer);
   printf("OpenGL version supported %s\n", version);
}

int main(int argc, char *argv[]) {
   int win_width;
   int win_height;
   std::string win_name;

   getArguments(argc, argv, &win_width, &win_height, &win_name);

   GLFWwindow *window = nullptr;

   if (!glfwInit()) { //Obsługa błedów
      exit(EXIT_FAILURE);
   }

   window = glfwCreateWindow(win_width, win_height, win_name.c_str(), NULL, NULL);
   if (!window) { //Obsługa błedów
      glfwTerminate(); //Usunięcie okna
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
   glfwSetKeyCallback(window, key_callback);
   glfwSetCursorPosCallback(window, mouse_position_callback);
   glfwSetMouseButtonCallback(window, mouse_button_callback);
   glfwSetScrollCallback(window, mouse_scroll_callback);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   ShaderProgram program;
   program.AddShaderFromFile(GL_VERTEX_SHADER, "./../shaders/vertexShader.glsl");
   program.AddShaderFromFile(GL_FRAGMENT_SHADER, "./../shaders/fragmentShader.glsl");
   program.Link();

   GLint mvp_location;
   mvp_location = glGetUniformLocation(program.Get(), "MVP");

   GLuint VBO;
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);

   Mesh bladeRunnerMesh;
   bladeRunnerMesh.loadOBJ("./../assets/BladeRunner_blaster/BladeRunner_blaster.obj");

   glBufferData(GL_ARRAY_BUFFER, bladeRunnerMesh.vertices.size() * sizeof(glm::vec3), &bladeRunnerMesh.vertices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
   glEnableVertexAttribArray(0);


   GLuint UVbuffer;
   glGenBuffers(1, &UVbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, UVbuffer);
   glBufferData(GL_ARRAY_BUFFER, bladeRunnerMesh.uvs.size() * sizeof(glm::vec2), &bladeRunnerMesh.uvs[0], GL_STATIC_DRAW);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
   glEnableVertexAttribArray(1);
   glBindVertexArray(0);

   Camera camera;

   Texture wallTexture;
   wallTexture.loadTexture("./../assets/BladeRunner_blaster/textures/blaster_albedo.tga");
   glBindTexture(GL_TEXTURE_2D, wallTexture.texture);

   InputProcessor inputProcessor = InputProcessor::getInputProcessor();

   float lastFrame = 0;
   float deltaTime = 0;

   while (!glfwWindowShouldClose(window)) {
      //////DELTA TIME CALCULATION//////
      deltaTime = (float) glfwGetTime() - lastFrame;
      lastFrame += deltaTime;
      //////DELTA TIME CALCULATION//////

      inputProcessor.update();
      camera.update(deltaTime);

      program.Use();

      glfwGetWindowSize(window, &win_width, &win_height);
      float ratio = win_width / (float) win_height;
      glViewport(0, 0, win_width, win_height);

      glClearColor(0.4f, 0.6f, 0.6f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      glm::mat4 m, v, p, mvp;
      m = glm::mat4(1.0);
      v = glm::mat4(1.0);

      m = glm::scale(m, glm::vec3(1.0f, 1.0f, 1.0f));

      v = camera.GetViewMatrix();

      p = glm::perspective(glm::radians(45.f), ratio, 0.1f, 100.f);

      mvp = p * v * m;
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

      glDrawArrays(GL_TRIANGLES, 0, bladeRunnerMesh.vertices.size());

      glBindVertexArray(0);
      glfwSwapBuffers(window);
   }

   glfwTerminate();

   exit(EXIT_SUCCESS);
}



