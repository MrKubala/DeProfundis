#include "Texture.h"

void Texture::loadTexture(std::string fileName) {
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

   int width, height;
   unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
   glGenerateMipmap(GL_TEXTURE_2D);
   SOIL_free_image_data(image);

   glBindTexture(GL_TEXTURE_2D, 0);
}