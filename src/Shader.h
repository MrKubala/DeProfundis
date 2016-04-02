#ifndef DEPROFUNDIS_SHADER_H
#define DEPROFUNDIS_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {

public:
   Shader(const std::string& fileName);
   virtual ~Shader();
   void bind();

   static const std::string SHADERS_DIR;

private:
   static const unsigned int NUM_SHADERS = 2;
   GLuint m_program;
   GLuint m_shaders[NUM_SHADERS];

};


#endif //DEPROFUNDIS_SHADER_H
