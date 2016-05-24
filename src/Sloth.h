#ifndef SLOTHENGINE_SLOTH_H
#define SLOTHENGINE_SLOTH_H

#include <list>
#include "PhongShader.h"
#include "Light.h"

class Sloth {
public:
   static PhongShader *phongShader;
   static int *windowsWidth;
   static int *windowsHeight;
   static bool freeMouseMode;
   static int *framesPerSecond;
   static std::list<Light> *lightsObjects;
};


#endif //SLOTHENGINE_SLOTH_H
