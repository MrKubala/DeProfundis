#include "Camera.h"

void Camera::update(float deltaTime) {
   PhongShader &phongShader = *Sloth::phongShader;
   viewPerspectiveMatrixUniformLocation = phongShader.viewPerspectiveMatrixUniformLocation;
   InputProcessor* inputProcessor = InputProcessor::getInputProcessor();

   if(inputProcessor->inputState[GLFW_KEY_W])
      ProcessKeyboard(FORWARD, deltaTime);
   if(inputProcessor->inputState[GLFW_KEY_S])
      ProcessKeyboard(BACKWARD, deltaTime);
   if(inputProcessor->inputState[GLFW_KEY_A])
      ProcessKeyboard(LEFT, deltaTime);
   if(inputProcessor->inputState[GLFW_KEY_D])
      ProcessKeyboard(RIGHT, deltaTime);

   GLfloat xOff = (GLfloat)inputProcessor->getMouseXOffset();
   GLfloat yOff = (GLfloat)inputProcessor->getMouseYOffset();
   ProcessMouseMovement(xOff, yOff);

   glUniform3fv(Sloth::phongShader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(position));
   setViewPerspectiveMatrix();
}

void Camera::setViewPerspectiveMatrix() {
   viewPerspectiveMatrix = glm::perspective(glm::radians(zoom), ratio, nearClip, farClip) * glm::lookAt(this->position, this->position + this->front, this->up);

   glUniformMatrix4fv(viewPerspectiveMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewPerspectiveMatrix));
}