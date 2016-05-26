#ifndef SLOTHENGINE_SLOTHENGINEPROGRAM_H
#define SLOTHENGINE_SLOTHENGINEPROGRAM_H
#define MANY_OBJECTS_DEMO1

#include <list>
#include "ShaderProgramCreator.h"
#include "Camera.h"
#include "GameObject.h"
#include "LightingManager.h"
#include "AntTweakBar/AntTweakBar.h"
#include "ATB.h"

typedef enum { CUBE, COMMANDO, BLASTER, KNIGHT } MESH_TYPE;

class SlothEngineProgramSample {
public:
   void create();
   void render(float deltaTime);
   void update(float deltaTime);
   void setMainATBBar();

private:
   ATB *atb;
   bool canToggleMainBar;

   InputProcessor *inputProcessor;

   Camera *camera;
#ifdef MANY_OBJECTS_DEMO
   std::vector<GameObject> blasters;
   std::vector<GameObject> commandos;
   std::vector<GameObject> knights;
   int numOfGameObjects;
#else
   GameObject *cubeModel;
   GameObject *commandoModel;
   GameObject *blasterModel;
   GameObject *knightModel;
#endif
   MESH_TYPE m_currentMesh = CUBE;

   void loadObj();

   glm::vec3 ambientLightColor;
   LightingManager *lightingManager;
   Light directionalLight;
   Light dynamicLight;
   std::list<Light> lightsObjects;
   GameObject *lightCube;
   float timeSinceBeginning = 0;
   float lightsMinRadius = 9;

   float specularPower = 35;
   float specularIntensity = 0.25;

};


#endif //SLOTHENGINE_SLOTHENGINEPROGRAM_H
