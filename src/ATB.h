#ifndef SLOTHENGINE_ANB_H
#define SLOTHENGINE_ANB_H

#include <AntTweakBar/AntTweakBar.h>
#include <glm/vec3.hpp>
extern TwType TW_TYPE_VECTOR3F;

class ATB {
public:
   ATB() { }

   void init();

   void draw();

   TwBar *bar;

};

#endif //SLOTHENGINE_ANB_H
