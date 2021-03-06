#include <AntTweakBar/AntTweakBar.h>
#include "InputProcessor.h"
#include "Sloth.h"

void InputProcessor::update() {
   resetMouseOffset();
   glfwPollEvents();
}

void InputProcessor::handleKeyPressed(int key) {
   if (key == GLFW_KEY_GRAVE_ACCENT && Sloth::cameraRotation) {
      Sloth::cameraRotation = false;
   }
   else if (key == GLFW_KEY_GRAVE_ACCENT && !Sloth::cameraRotation) Sloth::cameraRotation = true;

   this->keyboardKeysState[key] = true;
}

void InputProcessor::handleKeyReleased(int key) {
   this->keyboardKeysState[key] = false;
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
   InputProcessor *inputProcessor = InputProcessor::getInputProcessor();

   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }
   else if (action == GLFW_PRESS) {
      TwKeyPressed(key, mods);
      inputProcessor->handleKeyPressed(key);
   }
   else if (action == GLFW_RELEASE) {
      inputProcessor->handleKeyReleased(key);
   }

}

void InputProcessor::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
   TwMouseButtonID btn = (button == GLFW_MOUSE_BUTTON_LEFT) ? TW_MOUSE_LEFT : TW_MOUSE_RIGHT;
   TwMouseAction ma = (action == GLFW_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
   TwMouseButton(ma, btn);

   InputProcessor *inputProcessor = InputProcessor::getInputProcessor();
   if (action == GLFW_PRESS) {
      inputProcessor->handleMouseButtonPressed(button);
   }
   else if (action == GLFW_RELEASE) {
      inputProcessor->handleMouseButtonReleased(button);
   }
}

void InputProcessor::mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {

}

void InputProcessor::mouse_position_callback(GLFWwindow *window, double xpos, double ypos) {

   TwMouseMotion(xpos, ypos);
   InputProcessor::getInputProcessor()->handleMouseMovement(xpos, ypos);

}

void InputProcessor::handleMouseButtonPressed(int button) {
   this->mouseButtonsState[button] = true;
}

void InputProcessor::handleMouseButtonReleased(int button) {
   this->mouseButtonsState[button] = false;
}



