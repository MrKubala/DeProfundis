#ifndef SLOTHENGINE_SLOTHENGINEPROGRAM_H
#define SLOTHENGINE_SLOTHENGINEPROGRAM_H


#include "ShaderProgramCreator.h"
#include "Camera.h"
#include "GameObject.h"
#include "LightingManager.h"
#include "AntTweakBar/AntTweakBar.h"
#include "ATB.h"

class SlothEngineProgramSample {
public:
   void create();
   void render(float deltaTime);
   void update(float deltaTime);
   void setMainATBBar();

private:
   ATB *atb;


   Camera *camera;
   std::vector<GameObject> blasters;
   std::vector<GameObject> commandos;
   std::vector<GameObject> knights;
   int numOfGameObjects;

   glm::vec3 ambientLightColor;
   LightingManager *lightingManager;
   Light directionalLight;
   std::vector<Light> lightsObjects;
   Light dynamicLight;
   GameObject *cube;
   float timeSinceBeginning = 0;
   float lightsMinRadius = 9;

   float specularPower = 35;
   float specularIntensity = 0.25;
};


#endif //SLOTHENGINE_SLOTHENGINEPROGRAM_H
