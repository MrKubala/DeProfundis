#include "Sloth.h"

PhongShader *Sloth::phongShader;
int *Sloth::windowsWidth;
int *Sloth::windowsHeight;
bool Sloth::freeMouseMode = true;
bool Sloth::displayAsWireframe = false;
int *Sloth::framesPerSecond;
std::list<Light> *Sloth::lightsObjects;
