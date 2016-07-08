#ifndef SLOTHENGINE_SLOTH_H
#define SLOTHENGINE_SLOTH_H

#include <list>
#include "Shader.h"

class Sloth {
public:
   static Shader *phongShader;
   static int *windowsWidth;
   static int *windowsHeight;
   static bool cameraRotation;
   static bool displayAsWireframe;
   static int *framesPerSecond;
};


#endif //SLOTHENGINE_SLOTH_H
