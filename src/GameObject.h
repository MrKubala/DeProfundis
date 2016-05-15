#ifndef SLOTHENGINE_GAMEOBJECT_H
#define SLOTHENGINE_GAMEOBJECT_H

#include "Mesh.h"
#include "Texture.h"
#include "OpenGL.hpp"
#include "Sloth.h"

class GameObject {
public:
   glm::vec3 position;
   glm::vec3 rotation;
   glm::vec3 scale;
   GameObject(Mesh &mesh, Texture &texture);
   void draw();
private:
   Mesh mesh;
   Texture texture;
   GLuint VAO;
   GLint modelMatrixLocation;
   glm::mat4 modelMatrix;
};


#endif //SLOTHENGINE_GAMEOBJECT_H
