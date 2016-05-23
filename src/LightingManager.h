#ifndef SLOTHENGINE_LIGHTNINGMANAGER_H
#define SLOTHENGINE_LIGHTNINGMANAGER_H


#include <vector>
#include <string>

#include "Light.h"
#include "Sloth.h"

class LightingManager {
public:
   std::vector<Light *> lights;
   int getNumberOfLights();
   void addLight(Light *light);
   void removeLight(int lightToRemoveID);
   void removeLight(Light &lightToRemove);
   void processLights();
   static LightingManager &get();
private:
   LightingManager(){};
   int numberOfLights = 0;
   std::string LIGHT_DATA_UNIFORM_PREFIX = "lightsData";
   std::string getUniformLightName(std::string lightDataMember, int index);
};

#endif //SLOTHENGINE_LIGHTNINGMANAGER_H