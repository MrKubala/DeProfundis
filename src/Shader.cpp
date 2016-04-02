#include <fstream>
#include <iostream>
#include <string.h>
#include "Shader.h"

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
static std::string loadShader(const std::string &fileName);
static GLuint createShader(const std::string &text, GLenum shaderType);

const std::string Shader::SHADERS_DIR = "./../shaders/";

Shader::Shader(const std::string &fileName) {
   m_program = glCreateProgram();
   m_shaders[0] = createShader(loadShader(fileName + ".vert"), GL_VERTEX_SHADER);
   m_shaders[1] = createShader(loadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

   for (int i = 0; i < NUM_SHADERS; i++) {
      glAttachShader(m_program, m_shaders[i]);
   }

   glBindAttribLocation(m_program, 0, "position");

   glLinkProgram(m_program);
   checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

   glValidateProgram(m_program);
   checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

Shader::~Shader() {
   for (int i = 0; i < NUM_SHADERS; i++) {
      glDetachShader(m_program, m_shaders[i]);
      glDeleteProgram(m_shaders[i]);
   }

   glDeleteProgram(m_program);
}

void Shader::bind() {
   glUseProgram(m_program);
}

static GLuint createShader(const std::string &text, GLenum shaderType) {
   GLuint shader = glCreateShader(shaderType);

   if (shader == 0) {
      std::cerr << "Error: Shader creation failed!" << std::endl;
   }

   const GLchar *shaderSourceStrings[1];
   GLint shaderSourceStringsLengths[1];

   shaderSourceStrings[0] = text.c_str();
   shaderSourceStringsLengths[0] = text.length();

   glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
   glCompileShader(shader);

   checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

   return shader;
}

static std::string loadShader(const std::string &fileName) {
   std::string shaderLocalization = (Shader::SHADERS_DIR + fileName);

   std::ifstream file;
   file.open(shaderLocalization);

   std::string output;
   std::string line;

   if (file.is_open()) {
      while (file.good()) {
         getline(file, line);
         output.append(line + "\n");
         std::cout << line << std::endl;
      }
   }
   else {
      std::cerr << "Unable to load shader: " << shaderLocalization << std::endl;
      std::cerr << strerror(errno) << std::endl;
   }

   return output;
}

void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage) {
   GLint success = 0;
   GLchar error[1024] = {0};

   if (isProgram)
      glGetProgramiv(shader, flag, &success);
   else
      glGetShaderiv(shader, flag, &success);

   if (success == GL_FALSE) {
      if (isProgram)
         glGetProgramInfoLog(shader, sizeof(error), NULL, error);
      else
         glGetShaderInfoLog(shader, sizeof(error), NULL, error);

      std::cerr << errorMessage << ": '" << error << "'" << std::endl;
   }
}