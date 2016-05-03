/* GLFWControls.hpp
 * Zarządzanie sterowaniem w GLFW.
 * (C) Jan Bielański 2016
 */

#include "GLFWControls.hpp"
#include "InputProcessor.h"
#include <iostream>

// Obsługa błędów GLFW
void error_callback(int error, const char* description)
{
  std::cerr<<"Error code: "<<error<<" ; Description: "<<description<<std::endl;
}

// Obsługa klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  InputProcessor inputProcessor = InputProcessor::getInputProcessor();

  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  else if(action == GLFW_PRESS) {
    inputProcessor.handleKeyPressed(key);
  }
  else if(action == GLFW_RELEASE) {
    inputProcessor.handleKeyReleased(key);
  }
}

// Obsługa przycisków myszy
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if(action == GLFW_PRESS) {
    std::cout<<"Mouse button "<<button<<" is pressed."<<std::endl;
  }
}

// Obsługa rolki myszy
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

// Obsługa położenia kursora
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  InputProcessor inputProcessor = InputProcessor::getInputProcessor();
  inputProcessor.handleMouseMovement(xpos, ypos);
}

