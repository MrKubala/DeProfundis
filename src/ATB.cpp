#include "ATB.h"
#include "Sloth.h"
TwType TW_TYPE_VECTOR3F;
void ATB::init() {
   TwInit(TW_OPENGL, NULL);
   TwWindowSize(*Sloth::windowsWidth, *Sloth::windowsHeight);

   TwStructMember Vector3fMembers[] = {
      {"x", TW_TYPE_FLOAT, offsetof(glm::vec3, x), "step=0.02"},
      {"y", TW_TYPE_FLOAT, offsetof(glm::vec3, y), "step=0.02"},
      {"z", TW_TYPE_FLOAT, offsetof(glm::vec3, z), "step=0.02"}
   };

   TW_TYPE_VECTOR3F = TwDefineStruct("Vector3f", Vector3fMembers, 3, sizeof(glm::vec3), NULL, NULL);

   bar = TwNewBar("OGLDEV");
}

void ATB::draw() {
   TwDraw();
}



