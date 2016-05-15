#ifndef SLOTHENGINE_LIGHTNINGMANAGER_H
#define SLOTHENGINE_LIGHTNINGMANAGER_H


#include <vector>
#include "Light.h"

class LightingManager {
public:
   int getNumberOfLights();
   void addLight(Light light);
   void processLights();
private:
   int numberOfLights;
   std::vector<Light> lights;
};


#endif //SLOTHENGINE_LIGHTNINGMANAGER_H
