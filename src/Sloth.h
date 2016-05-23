#ifndef SLOTHENGINE_SLOTH_H
#define SLOTHENGINE_SLOTH_H

#include "PhongShader.h"

class Sloth {
public:
   static PhongShader *phongShader;
   static int *windowsWidth;
   static int *windowsHeight;
   static bool freeMouseMode;
};


#endif //SLOTHENGINE_SLOTH_H
