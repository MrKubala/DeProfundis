#ifndef SLOTHENGINE_SLOTH_H
#define SLOTHENGINE_SLOTH_H

#include "PhongShader.h"
#include "Light.h"

class Sloth {
public:
   static PhongShader *phongShader;
   static int *windowsWidth;
   static int *windowsHeight;
   static bool freeMouseMode;
   static int *framesPerSecond;
   static std::vector<Light> *lightsObjects;
};


#endif //SLOTHENGINE_SLOTH_H
