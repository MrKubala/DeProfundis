#ifndef SLOTHENGINE_LIGHTING_H
#define SLOTHENGINE_LIGHTING_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

struct Light {
   int ID;
   static int entitiesCounter;
   glm::vec4 position;
   glm::vec3 color;
   float attenuation;
   float coneAngle;
   glm::vec3 coneDirection;


   Light():ID(entitiesCounter), color(glm::vec3(1.0f, 1.0f, 1.0f)), attenuation(0.4f), coneAngle(23.1415){
      entitiesCounter++;
   }
};

#endif //SLOTHENGINE_LIGHTING_H
