#ifndef SLOTHENGINE_SLOTHENGINEPROGRAM_H
#define SLOTHENGINE_SLOTHENGINEPROGRAM_H


#include "ShaderProgramCreator.h"
#include "Camera.h"
#include "GameObject.h"
#include "LightingManager.h"

class SlothEngineProgramSample {
public:
   void create();
   void render(float deltaTime);
   void update(float deltaTime);

private:
   Camera *camera;
   std::vector<GameObject> blasters;
   std::vector<GameObject> commandos;
   int numOfGameObjects;
   LightingManager lightingManager;
   Light directionalLight;
   Light light1;
   Light light2;
   GameObject *cube;
   float timeSinceBegining = 0;
   float lightsMinRadius = 9;

   float specularPower = 35;
   float specularIntensity = 0.35;
};


#endif //SLOTHENGINE_SLOTHENGINEPROGRAM_H
