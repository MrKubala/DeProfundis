#ifndef SLOTHENGINE_SLOTHENGINEPROGRAM_H
#define SLOTHENGINE_SLOTHENGINEPROGRAM_H


#include "ShaderProgram.h"
#include "Camera.h"
#include "GameObject.h"

class SlothEngineProgramSample {
public:
   void create();
   void render(float deltaTime);
   void update(float deltaTime);

private:
   Camera *camera;
   std::vector<GameObject> blasters;
   int numOfGameObjects;
};


#endif //SLOTHENGINE_SLOTHENGINEPROGRAM_H
