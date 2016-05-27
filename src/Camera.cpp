#include "Camera.h"

void Camera::update(float deltaTime) {
   PhongShader &phongShader = *Sloth::phongShader;
   viewPerspectiveMatrixUniformLocation = phongShader.viewPerspectiveMatrixUniformLocation;
   InputProcessor *inputProcessor = InputProcessor::getInputProcessor();

   if (inputProcessor->keyboardKeysState[GLFW_KEY_W])
      processKeyboard(FORWARD, deltaTime);
   if (inputProcessor->keyboardKeysState[GLFW_KEY_S])
      processKeyboard(BACKWARD, deltaTime);
   if (inputProcessor->keyboardKeysState[GLFW_KEY_A])
      processKeyboard(LEFT, deltaTime);
   if (inputProcessor->keyboardKeysState[GLFW_KEY_D])
      processKeyboard(RIGHT, deltaTime);

   if (Sloth::cameraRotation) {
      GLfloat xOff = (GLfloat) inputProcessor->getMouseXOffset();
      GLfloat yOff = (GLfloat) inputProcessor->getMouseYOffset();
      processMouseMovement(xOff, yOff);
   }
   updateCameraVectors();

   glUniform3fv(Sloth::phongShader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(position));
   setViewPerspectiveMatrix();
}

void Camera::setViewPerspectiveMatrix() {
   viewPerspectiveMatrix = glm::perspective(glm::radians(zoom), ratio, nearClip, farClip) * glm::lookAt(this->position, this->position + this->front, this->up);

   glUniformMatrix4fv(viewPerspectiveMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewPerspectiveMatrix));
}