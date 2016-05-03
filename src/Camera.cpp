#include <iostream>
#include "Camera.h"

void Camera::update(float deltaTime) {
   InputProcessor inputProcessor = InputProcessor::getInputProcessor();

   if(inputProcessor.inputState[GLFW_KEY_W])
      ProcessKeyboard(FORWARD, deltaTime);
   if(inputProcessor.inputState[GLFW_KEY_S])
      ProcessKeyboard(BACKWARD, deltaTime);
   if(inputProcessor.inputState[GLFW_KEY_A])
      ProcessKeyboard(LEFT, deltaTime);
   if(inputProcessor.inputState[GLFW_KEY_D])
      ProcessKeyboard(RIGHT, deltaTime);

   GLfloat xOff = (GLfloat)inputProcessor.getMouseXOffset();
   GLfloat yOff = (GLfloat)inputProcessor.getMouseYOffset();
   ProcessMouseMovement(xOff, yOff);
}