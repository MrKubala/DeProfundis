#include "LightingManager.h"

void LightingManager::processLights() {

}

int LightingManager::getNumberOfLights() {
   return numberOfLights;
}

void LightingManager::addLight(Light light) {
   lights.push_back(light);
   numberOfLights++;
}





