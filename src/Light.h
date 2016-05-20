//
// Created by Kuba on 2016-05-15.
//

#ifndef SLOTHENGINE_LIGHTING_H
#define SLOTHENGINE_LIGHTING_H


#include "LightsTypeEnum.h"

class Light {
public:
   const int lightID;
   const LightType lightType;
private:
   static int counter;
};


#endif //SLOTHENGINE_LIGHTING_H
