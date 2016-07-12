#ifndef SLOTHENGINE_SLOTHENGINEPROGRAM_H
#define SLOTHENGINE_SLOTHENGINEPROGRAM_H

#include <list>
#include "ShaderProgramCreator.h"
#include "Camera.h"
#include "GameObject.h"
#include "AntTweakBar/AntTweakBar.h"

class SlothEngineProgramSample {
public:
   void create();
   void render(float deltaTime);
   void update(float deltaTime);

private:
   InputProcessor *inputProcessor;

   Camera *camera;
   std::vector<GameObject> gameObjects;

   glm::vec3 clearColor = glm::vec3(.1f, .1f, .1f);
   glm::vec3 ambientLight = glm::vec3(1.0f, 1.0f, 1.0f);

   float timeSinceBeginning = 0;
};


#endif //SLOTHENGINE_SLOTHENGINEPROGRAM_H
