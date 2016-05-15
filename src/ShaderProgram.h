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
   // Usuwanie shadera
   void Remove();

   // Konstruktor
   ShaderObject(GLuint shader_type);

   // Destruktor
   ~ShaderObject();

   // -------------------------------------------------------------------------------

   GLuint type; // Typ shadera [ GL_VERTEX_SHADER /
   //               GL_TESS_CONTROL_SHADER / GL_TESS_EVALUATION_SHADER /
   //               GL_GEOMETRY_SHADER /
   //               GL_FRAGMENT_SHADER /
   //               GL_COMPUTE_SHADER

   GLuint object; // Obiekt shadera
};

class ShaderProgram {
public:

   void addShaderWithSources(GLuint shader_type, const char *shader_code);

   void addShaderFromFile(GLuint shader_type, const char *file_name);

   void link();

   void use();

   GLuint get();

   void deleteShaderProgram();

   ShaderProgram();

   ~ShaderProgram();

   GLint modelMatrixUniformLocation;
   GLint viewPerspectiveMatrixUniformLocation;

private:
   bool loadCode(GLchar **data, const char *file_name);

   void deleteShaders();

   std::vector<struct ShaderObject *> shaders;

   GLuint program;


   bool error_flag;
   bool link_flag;
};


GLuint loadShader(const char *shader_code, GLuint shader_type);

GLuint loadShaderFromFile(const char *file_name, GLuint shader_type);

void removeShader(GLuint program, GLuint shader);

#endif

