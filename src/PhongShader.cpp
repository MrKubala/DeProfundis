#include <stdexcept>
#include <iostream>
#include "PhongShader.h"
void PhongShader::bind() {
   glUseProgram(shaderProgram);
   modelMatrixUniformLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
   viewPerspectiveMatrixUniformLocation = glGetUniformLocation(shaderProgram, "viewPerspectiveMatrix");
}

PhongShader::PhongShader(const char *vertex_shader, const char *fragment_shader) {
   ShaderProgramCreator shaderProgramCreator;
   shaderProgramCreator.addShaderFromFile(GL_VERTEX_SHADER, vertex_shader);
   shaderProgramCreator.addShaderFromFile(GL_FRAGMENT_SHADER, fragment_shader);
   shaderProgram = 0;
   shaderProgramCreator.link(shaderProgram);
}

GLint PhongShader::getUniformLocation(const GLchar *uniformName){
   GLint uniform = glGetUniformLocation(shaderProgram, uniformName);
   if(uniform == -1)
      std::cerr << "Program uniform not found: " + std::string(uniformName) + "\n";

   return uniform;
}



