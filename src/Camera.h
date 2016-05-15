#ifndef DEPROFUNDIS_CAMERA_H
#define DEPROFUNDIS_CAMERA_H


#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "InputProcessor.h"
#include "Sloth.h"


const GLfloat CAMERA_YAW = -90.0f;
const GLfloat CAMERA_PITCH = 0.0f;
const GLfloat CAMERA_SPEED = 3.0f;
const GLfloat CAMERA_SENSITIVTY = 0.25f;
const GLfloat CAMERA_ZOOM = 45.0f;

class Camera {
public:
   // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
   enum Camera_Movement {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
   };

   GLint viewPerspectiveMatrixUniformLocation;
   glm::mat4 viewPerspectiveMatrix;


   glm::vec3 position;
   glm::vec3 front;
   glm::vec3 up;
   glm::vec3 right;
   glm::vec3 worldUp;

   GLfloat yaw;
   GLfloat pitch;

   GLfloat movementSpeed;
   GLfloat mouseSensitivity;
   GLfloat zoom;

   GLfloat ratio;

   float nearClip = 0.1f;
   float farClip = 100.f;


   Camera(GLfloat ratio, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
          GLfloat yaw = CAMERA_YAW, GLfloat pitch = CAMERA_PITCH)
   : ratio(ratio),
     front(glm::vec3(0.0f, 0.0f, -1.0f)),
     movementSpeed(CAMERA_SPEED),
     mouseSensitivity(CAMERA_SENSITIVTY),
     zoom(CAMERA_ZOOM) {
      this->position = position;
      this->worldUp = up;
      this->yaw = yaw;
      this->pitch = pitch;
      this->updateCameraVectors();
   }


   void setViewPerspectiveMatrix();

   void update(float deltaTime);

   void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
      GLfloat velocity = this->movementSpeed * deltaTime;
      if (direction == FORWARD)
         this->position += this->front * velocity;
      if (direction == BACKWARD)
         this->position -= this->front * velocity;
      if (direction == LEFT)
         this->position -= this->right * velocity;
      if (direction == RIGHT)
         this->position += this->right * velocity;
   }


   void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
      xoffset *= this->mouseSensitivity;
      yoffset *= this->mouseSensitivity;

      this->yaw += xoffset;
      this->pitch += yoffset;

      if (constrainPitch) {
         if (this->pitch > 89.0f)
            this->pitch = 89.0f;
         if (this->pitch < -89.0f)
            this->pitch = -89.0f;
      }


      this->updateCameraVectors();
   }


   void ProcessMouseScroll(GLfloat yoffset) {
      if (this->zoom >= 1.0f && this->zoom <= 45.0f)
         this->zoom -= yoffset;
      if (this->zoom <= 1.0f)
         this->zoom = 1.0f;
      if (this->zoom >= 45.0f)
         this->zoom = 45.0f;
   }

private:

   void updateCameraVectors() {

      glm::vec3 front;
      front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
      front.y = sin(glm::radians(this->pitch));
      front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
      this->front = glm::normalize(front);
      this->right = glm::normalize(glm::cross(this->front, this->worldUp));
      this->up = glm::normalize(glm::cross(this->right, this->front));
   }

};

#endif //DEPROFUNDIS_CAMERA_H
