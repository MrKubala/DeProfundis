#include "Camera.h"

void Camera::update(float deltaTime) {
   Shader &shader = *Sloth::phongShader;
   viewPerspectiveMatrixUniformLocation = shader.viewPerspectiveMatrixUniformLocation;
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

   setViewPerspectiveMatrix();
}

void Camera::setViewPerspectiveMatrix() {
   viewPerspectiveMatrix = glm::perspective(glm::radians(zoom), ratio, nearClip, farClip) * glm::lookAt(this->position, this->position + this->front, this->up);

   glUniformMatrix4fv(viewPerspectiveMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewPerspectiveMatrix));
}