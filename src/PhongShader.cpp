#include "PhongShader.h"
void PhongShader::bind() {
   glUseProgram(this->shaderProgram);
   this->modelMatrixUniformLocation = glGetUniformLocation(this->shaderProgram, "ModelMatrix");
   this->viewPerspectiveMatrixUniformLocation = glGetUniformLocation(this->shaderProgram, "ViewPerspectiveMatrix");
   this->ambientLightColorUniformLocation = glGetUniformLocation(this->shaderProgram, "ambientLightColor");
}

PhongShader::PhongShader(const char *vertex_shader, const char *fragment_shader) {
   ShaderProgramCreator shaderProgramCreator;
   shaderProgramCreator.addShaderFromFile(GL_VERTEX_SHADER, vertex_shader);
   shaderProgramCreator.addShaderFromFile(GL_FRAGMENT_SHADER, fragment_shader);
   shaderProgram = 0;
   shaderProgramCreator.link(shaderProgram);
}

