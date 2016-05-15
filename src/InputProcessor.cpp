#include "InputProcessor.h"

void InputProcessor::update() {
   resetMouseOffset();
   glfwPollEvents();
}

void InputProcessor::handleKeyPressed(int key) {
   this->inputState[key] = true;
}

void InputProcessor::handleKeyReleased(int key) {
   this->inputState[key] = false;
}

void InputProcessor::handleMouseMovement(double xPos, double yPos) {
   this->mouseLastXPos = this->mouseXPos;
   this->mouseLastYPos = this->mouseYPos;
   this->mouseXPos = xPos;
   this->mouseYPos = yPos;
}


void InputProcessor::resetMouseOffset() {
   this->mouseLastXPos = this->mouseXPos;
   this->mouseLastYPos = this->mouseYPos;
}

double InputProcessor::getMouseXOffset() { return mouseXPos - mouseLastXPos; }

double InputProcessor::getMouseYOffset() { return mouseLastYPos - mouseYPos; }

void InputProcessor::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
   InputProcessor* inputProcessor = InputProcessor::getInputProcessor();

   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }
   else if (action == GLFW_PRESS) {
      inputProcessor->handleKeyPressed(key);
   }
   else if (action == GLFW_RELEASE) {
      inputProcessor->handleKeyReleased(key);
   }
}

void InputProcessor::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
   if (action == GLFW_PRESS) {
   }
}

void InputProcessor::mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {

}

void InputProcessor::mouse_position_callback(GLFWwindow *window, double xpos, double ypos) {
   InputProcessor* inputProcessor = InputProcessor::getInputProcessor();
   inputProcessor->handleMouseMovement(xpos, ypos);
}