/* ShaderProgram.hpp
 * Biblioteka udostępnia klasę umozliwiającą łatwe zarządzanie
 * programami shaderów.
 *
 * (C) Jan Bielański 2016
 */

#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include "OpenGL.hpp"
#include <vector>

struct ShaderObject {
   ShaderObject(GLuint shader_type);

   ~ShaderObject();

   GLuint type;
   GLuint object;
};

class ShaderProgramCreator {
public:

   void addShaderFromFile(GLuint shader_type, const char *file_name);

   void link(GLuint &shaderProgram);
   ShaderProgramCreator();

   ~ShaderProgramCreator();


private:
   bool loadCode(GLchar **data, const char *file_name);

   void deleteShaders();
   void deleteShaderProgram();

   std::vector<struct ShaderObject *> shaders;

   GLuint shaderProgram;

   bool error_flag;
   bool link_flag;
};

#endif

