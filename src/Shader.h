#ifndef SLOTHENGINE_PHONGSHADER_H
#define SLOTHENGINE_PHONGSHADER_H

#include <GL/glew.h>
#include "ShaderProgramCreator.h"

class Shader {
public:
   GLuint shaderProgram;

   GLint modelMatrixUniformLocation;
   GLint viewPerspectiveMatrixUniformLocation;

   void bind();

   GLint getUniformLocation(const GLchar* uniformName);


   Shader(const char *vertex_shader, const char *fragment_shader);
};


#endif //SLOTHENGINE_PHONGSHADER_H
