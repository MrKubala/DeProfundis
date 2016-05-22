#include "LightingManager.h"

void LightingManager::processLights() {
   PhongShader& shaderProgram = *(Sloth::phongShader);

   glUniform1i(shaderProgram.getUniformLocation("numLights"), numberOfLights);

   for (int i = 0; i < lights.size(); i++) {
      glUniform4fv(shaderProgram.getUniformLocation(getUniformLightName("position", i).c_str()), 1, glm::value_ptr(lights[i]->position));
      glUniform3fv(shaderProgram.getUniformLocation(getUniformLightName("color", i).c_str()), 1, glm::value_ptr(lights[i]->color));
      glUniform1f(shaderProgram.getUniformLocation(getUniformLightName("attenuation", i).c_str()), lights[i]->attenuation);
      glUniform1f(shaderProgram.getUniformLocation(getUniformLightName("coneAngle", i).c_str()), lights[i]->coneAngle);
      glUniform3fv(shaderProgram.getUniformLocation(getUniformLightName("coneDirection", i).c_str()), 1, glm::value_ptr(lights[i]->coneDirection));
   }
}

int LightingManager::getNumberOfLights() {
   return numberOfLights;
}

void LightingManager::addLight(Light *light) {
   lights.push_back(light);
   numberOfLights++;
}

void LightingManager::removeLight(Light &lightToRemove) {
   for (std::vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++) {
      if ((*it)->ID == lightToRemove.ID) {
         lights.erase(it);
         break;
      }
   }
}

std::string LightingManager::getUniformLightName(std::string lightDataMember, int index) {
   return LIGHT_DATA_UNIFORM_PREFIX + "[" + std::to_string(index) + "]." + lightDataMember;
}

