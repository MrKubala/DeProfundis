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

struct ShaderObject
{
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

class ShaderProgram
{
public:

  // Dodawanie shadera - zródła shadera w tablicy
  void AddShaderWithSources(GLuint shader_type, const char *shader_code);

  // Dodawanie shadera - zródła shadera w pliku
  void AddShaderFromFile(GLuint shader_type, const char *file_name);

  // Linkowanie programu
  void Link();

  // Wykorzystanie programu 
  void Use();

  // Pobranie programu
  GLuint Get();

  // Usuwanie programu i shaderow
  void Delete();
  
  // Konstruktor
  ShaderProgram();

  // Destruktor
  ~ShaderProgram();

private:
  // Ładowanie kodu źródłowego
  bool LoadCode(GLchar **data, const char *file_name);

  // Usuwanie shaderów
  void DeleteShaders();
  
  // Wektor shaderów
  std::vector<struct ShaderObject*> shaders;

  // PROGRAM shadera
  GLuint program;

  // Flagi (błędu/linkowania)
  bool error_flag;
  bool link_flag;
};












GLuint LoadShader(const char *shader_code, GLuint shader_type);
GLuint LoadShaderFromFile(const char *file_name, GLuint shader_type);
void RemoveShader(GLuint program, GLuint shader);

#endif

