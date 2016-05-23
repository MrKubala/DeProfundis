#ifndef SLOTHENGINE_ANB_H
#define SLOTHENGINE_ANB_H

#include <AntTweakBar/AntTweakBar.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Light.h"
#include "LightingManager.h"
#include "Sloth.h"

extern TwType TW_TYPE_VECTOR3F;
extern TwType TW_TYPE_VECTOR4F;

struct RemoveLightBarStruct{
   std::vector<TwBar *> *lightBars;
   int lightID;
   RemoveLightBarStruct(std::vector<TwBar *> *vec, int ID):lightBars(vec), lightID(ID){}
};

const std::string LIGHT_BOX_PREFIX = "Light_";

class ATB {
public:
   ATB() { }

   void init();

   void draw();

   TwBar *mainBar;
   std::vector<TwBar *> lightBars;

   void addLightBar(Light *light);
};

#endif //SLOTHENGINE_ANB_H
