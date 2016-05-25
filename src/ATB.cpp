#include "ATB.h"

TwType TW_TYPE_VECTOR3F;
TwType TW_TYPE_VECTOR4F;



ATB &ATB::getInstanse() {
   static ATB atb;
   return atb;
}


void ATB::init() {
   TwInit(TW_OPENGL, NULL);
   TwWindowSize(*Sloth::windowsWidth, *Sloth::windowsHeight);

   TwStructMember Vector3fMembers[] = {
      {"x", TW_TYPE_FLOAT, offsetof(glm::vec3, x), "step=0.01"},
      {"y", TW_TYPE_FLOAT, offsetof(glm::vec3, y), "step=0.01"},
      {"z", TW_TYPE_FLOAT, offsetof(glm::vec3, z), "step=0.01"}
   };
   TwStructMember Vector4fMembers[] = {
      {"x", TW_TYPE_FLOAT, offsetof(glm::vec4, x), "step=0.01"},
      {"y", TW_TYPE_FLOAT, offsetof(glm::vec4, y), "step=0.01"},
      {"z", TW_TYPE_FLOAT, offsetof(glm::vec4, z), "step=0.01"},
      {"w", TW_TYPE_FLOAT, offsetof(glm::vec4, w), "step=1 min=0 max=1"}
   };

   TW_TYPE_VECTOR3F = TwDefineStruct("Vector3f", Vector3fMembers, 3, sizeof(glm::vec3), NULL, NULL);
   TW_TYPE_VECTOR4F = TwDefineStruct("Vector4f", Vector4fMembers, 4, sizeof(glm::vec4), NULL, NULL);

   mainBar = TwNewBar("SlothEngine");
   std::string position = "position='" + std::to_string(*Sloth::windowsWidth - mainBarWidth - mainBarXMargin)
                           + " " + std::to_string(mainBarYMargin) + "'";
   std::string size = "size='" + std::to_string(mainBarWidth) + " " + std::to_string(mainBarHeight) + "'";
   TwDefine(("SlothEngine " + position + " " + size + "valueswidth='135'").c_str());
}

void ATB::draw() {
   TwDraw();
}

void TW_CALL removeLightBar(void *clientData) {
   RemoveLightBarStruct data = *(RemoveLightBarStruct*)clientData;
   std::string barName = LIGHT_BOX_PREFIX + std::to_string(data.lightID);
   TwBar *barToDelete = TwGetBarByName(barName.c_str());
   TwDeleteBar( barToDelete);
   LightingManager::get().removeLight(data.lightID);


   for (std::vector<TwBar *>::iterator it = data.lightBars->begin(); it != data.lightBars->end(); it++) {
      if (*it == barToDelete) {
         data.lightBars->erase(it);
         break;
      }
   }
}

void ATB::addLightBar(Light *light) {
   std::string barName = LIGHT_BOX_PREFIX + std::to_string(light->ID);
   TwBar *bar = TwNewBar(barName.c_str());
   TwDefine((" " + barName + " size='270 180' valueswidth='135'").c_str());
   lightBars.push_back(bar);

   TwAddVarRW(lightBars.back(), "Position", TW_TYPE_VECTOR4F, (void*)&light->position, NULL);
   TwAddVarRW(lightBars.back(), "Color", TW_TYPE_COLOR3F, (void*)&light->color, NULL);
   TwAddVarRW(lightBars.back(), "Attenuation", TW_TYPE_FLOAT, (void*)&light->attenuation, "min=0 step=0.01");
   TwAddVarRW(lightBars.back(), "Cone Direction", TW_TYPE_DIR3F, (void*)&light->coneDirection, NULL);
   TwAddVarRW(lightBars.back(), "Cone Angle", TW_TYPE_FLOAT, (void*)&light->coneAngle, "min=0 max=90 step=0.01");
   TwAddSeparator(lightBars.back(), NULL, NULL);
   TwAddButton(lightBars.back(), "REMOVE LIGHT", removeLightBar, (void*)new RemoveLightBarStruct(&lightBars, light->ID), NULL);
}

void ATB::hideAllBars() {
   TwSetParam(mainBar, NULL, "visible", TW_PARAM_CSTRING, 1, "false");
   for(TwBar *twBar : lightBars){
      TwSetParam(twBar, NULL, "visible", TW_PARAM_CSTRING, 1, "false");
   }
}

void ATB::showAllBars() {
   TwSetParam(mainBar, NULL, "visible", TW_PARAM_CSTRING, 1, "true");
   for(TwBar *twBar : lightBars){
      TwSetParam(twBar, NULL, "visible", TW_PARAM_CSTRING, 1, "true");
   }
}

void ATB::toggleMainBarVisibility() {
//   char visible[8];
   int visible;
   TwGetParam(mainBar, NULL, "visible", TW_PARAM_INT32, 1, &visible);
   if(visible == 1){
      TwSetParam(mainBar, NULL, "visible", TW_PARAM_CSTRING, 1, "false");
   } else {
      TwSetParam(mainBar, NULL, "visible", TW_PARAM_CSTRING, 1, "true");
   }
}






