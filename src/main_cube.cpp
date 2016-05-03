#include <iostream>
#include <random>
#include "ProgramArguments.hpp"
#include "GLFWControls.hpp"
#include "ShaderProgram.hpp"
#include "Texture.h"
#include "InputProcessor.h"
#include "Camera.h"

void printOpenGLInfo(){
   const GLubyte *renderer = glGetString(GL_RENDERER);
   const GLubyte *version = glGetString(GL_VERSION);
   printf("Renderer: %s\n", renderer);
   printf("OpenGL version supported %s\n", version);
}

//Mesh createCube(glm::vec3 position, float size, Mesh* cube) {
//   float offset = size / 2;
//   Vertex vertices[] = {
//   Vertex(glm::vec3(position.x + offset, position.y + offset, position.z + offset)),//front
//   Vertex(glm::vec3(position.x - offset, position.y + offset, position.z + offset)),//front
//   Vertex(glm::vec3(position.x + offset, position.y - offset, position.z + offset)),//front
//   Vertex(glm::vec3(position.x - offset, position.y - offset, position.z + offset)),//front
//
//   Vertex(glm::vec3(position.x + offset, position.y + offset, position.z - offset)),//back
//   Vertex(glm::vec3(position.x - offset, position.y + offset, position.z - offset)),//back
//   Vertex(glm::vec3(position.x + offset, position.y - offset, position.z - offset)),//back
//   Vertex(glm::vec3(position.x - offset, position.y - offset, position.z - offset)),//back
//   };
//
//   cube = new Mesh(vertices, 8);
//}

GLfloat vertices[] = {
-0.5f, -0.5f, -0.5f,//back
-0.5f, 0.5f, -0.5f,//back
0.5f, -0.5f, -0.5f,//back
0.5f, 0.5f, -0.5f,//back
0.5f, -0.5f, -0.5f,//back
-0.5f, 0.5f, -0.5f,//back

-0.5f, -0.5f, 0.5f,//front
0.5f, -0.5f, 0.5f,//front
-0.5f, 0.5f, 0.5f,//front
0.5f, 0.5f, 0.5f,//front
-0.5f, 0.5f, 0.5f,//front
0.5f, -0.5f, 0.5f,//front

0.5f, 0.5f, 0.5f,//top
0.5f, 0.5f, -0.5f,//top
-0.5f, 0.5f, -0.5f,//top
-0.5f, 0.5f, 0.5f,//top
0.5f, 0.5f, 0.5f,//top
-0.5f, 0.5f, -0.5f,//top

0.5f, -0.5f, 0.5f,//bottom
-0.5f, -0.5f, -0.5f,//bottom
0.5f, -0.5f, -0.5f,//bottom
-0.5f, -0.5f, 0.5f,//bottom
-0.5f, -0.5f, -0.5f,//bottom
0.5f, -0.5f, 0.5f,//bottom

0.5f, -0.5f, 0.5f,//right
0.5f, -0.5f, -0.5f,//right
0.5f, 0.5f, 0.5f,//right
0.5f, 0.5f, -0.5f,//right
0.5f, 0.5f, 0.5f,//right
0.5f, -0.5f, -0.5f,//right

-0.5f, -0.5f, 0.5f,//left
-0.5f, 0.5f, 0.5f,//left
-0.5f, -0.5f, -0.5f,//left
-0.5f, 0.5f, -0.5f,//left
-0.5f, -0.5f, -0.5f,//left
-0.5f, 0.5f, 0.5f,//left

};

static const GLfloat uvBufferData[] = {
0.f, 0.f,
0.f, 1.f,
1.f, 0.f,
1.f, 1.f,
1.f, 0.f,
0.f, 1.f,

0.f, 0.f,
1.f, 0.f,
0.f, 1.f,
1.f, 1.f,
0.f, 1.f,
1.f, 0.f,

1.f, 1.f,
1.f, 0.f,
0.f, 0.f,
0.f, 1.f,
1.f, 1.f,
0.f, 0.f,

1.f, 1.f,
0.f, 0.f,
1.f, 0.f,
0.f, 1.f,
0.f, 0.f,
1.f, 1.f,

0.f, 1.f,
0.f, 0.f,
1.f, 1.f,
1.f, 0.f,
1.f, 1.f,
0.f, 0.f,

0.f, 1.f,
1.f, 1.f,
0.f, 0.f,
1.f, 0.f,
0.f, 0.f,
1.f, 1.f
};

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

   GLuint VAO;
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   GLuint VBO;
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, 3 * 6 * 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(0);


   GLuint UVbuffer;
   glGenBuffers(1, &UVbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, UVbuffer);
   glBufferData(GL_ARRAY_BUFFER, 2 * 6 * 6 * sizeof(GLfloat), uvBufferData, GL_STATIC_DRAW);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(1);
   glBindVertexArray(0);

   Camera camera;

   glm::vec3 cubePositions[] = {
   glm::vec3(0.0f, 0.0f, 0.0f),
   glm::vec3(2.0f, 5.0f, -15.0f),
   glm::vec3(-1.5f, -2.2f, -2.5f),
   glm::vec3(-3.8f, -2.0f, -12.3f),
   glm::vec3(2.4f, -0.4f, -3.5f),
   glm::vec3(-1.7f, 3.0f, -7.5f),
   glm::vec3(1.3f, -2.0f, -2.5f),
   glm::vec3(1.5f, 2.0f, -2.5f),
   glm::vec3(1.5f, 0.2f, -1.5f),
   glm::vec3(-1.3f, 1.0f, -1.5f)
   };

   Texture wallTexture;
   wallTexture.loadTexture("./../assets/wall.bmp");
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
      glBindVertexArray(VAO);

      glfwGetWindowSize(window, &win_width, &win_height);
      float ratio = win_width / (float) win_height;
      glViewport(0, 0, win_width, win_height);

      glClearColor(0.4f, 0.6f, 0.6f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      for (int i = 0; i < 10; i++) {
         glm::mat4 m, v, p, mvp;
         m = glm::mat4(1.0);
         v = glm::mat4(1.0);

         m = glm::translate(m, cubePositions[i]);
//         m = glm::rotate(m, (GLfloat) glm::radians(glfwGetTime()), glm::vec3(.4f, 0.6f, 0.0f));
         m = glm::scale(m, glm::vec3(1.0f, 1.0f, 1.0f));

         v = camera.GetViewMatrix();

         p = glm::perspective(glm::radians(45.f), ratio, 0.1f, 100.f);

         mvp = p * v * m;
         glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

         glDrawArrays(GL_TRIANGLES, 0, 108);

      }
      glBindVertexArray(0);
      glfwSwapBuffers(window);
   }

   glfwTerminate();

   exit(EXIT_SUCCESS);
}



