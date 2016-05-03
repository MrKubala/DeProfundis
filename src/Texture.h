#ifndef DEPROFUNDIS_TEXTURE_H
#define DEPROFUNDIS_TEXTURE_H


#include <GL/glew.h>
#include <string>
#include "SOIL/SOIL.h"

class Texture {
public:
   GLuint texture;
   void loadTexture(std::string fileName);
};


#endif //DEPROFUNDIS_TEXTURE_H
