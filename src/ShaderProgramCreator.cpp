#include "ShaderProgramCreator.h"
#include <iostream>

ShaderObject::ShaderObject(GLuint shader_type) {
   type = shader_type;
   object = 0;
}

ShaderObject::~ShaderObject() {
   if (object != 0) { glDeleteShader(object); }
}

void ShaderProgramCreator::addShaderFromFile(GLuint shader_type, const char *file_name) {

   shaders.push_back(new ShaderObject(shader_type));

   shaders.back()->object = glCreateShader(shaders.back()->type);

   if (shaders.back()->object != 0) {

      GLchar *data = nullptr;

      error_flag = loadCode(&data, file_name);

      if (data != nullptr || error_flag) {

         glShaderSource(shaders.back()->object, 1, const_cast<const GLchar **>(&data), NULL);

         glCompileShader(shaders.back()->object);

         GLint shader_status;
         glGetShaderiv(shaders.back()->object, GL_COMPILE_STATUS, &shader_status);
         if (shader_status != GL_TRUE) {
            std::cerr << "[ShaderProgramCreator::addShaderFromFile] Can not compile shader object!!!\n";
            error_flag = true;
         }

         free(data);

      } else {
         std::cerr << "[ShaderProgramCreator::addShaderFromFile] Shader source code does not exist!!!\n";
         error_flag = true;
      }
   } else {
      std::cerr << "[ShaderProgramCreator::addShaderFromFile] Can not create shader object!!!\n";
      error_flag = true;
   }

   if (error_flag) {
      delete shaders.back();
      shaders.pop_back();
      error_flag = false;
   }
}

void ShaderProgramCreator::link(GLuint &shaderProgram) {

   if (shaderProgram == 0) {
      shaderProgram = glCreateProgram();
   }

   if (glIsProgram(shaderProgram)) {
      if (!link_flag) {
         GLuint types[6] = {GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER,
                            GL_FRAGMENT_SHADER, GL_COMPUTE_SHADER};

         for (auto const &t : types) {
            for (auto const &shader : shaders) {
               if (shader->type == t) {
                  glAttachShader(shaderProgram, shader->object);
               }
            }
         }

         if (!link_flag) {
            glLinkProgram(shaderProgram);
            link_flag = true;
         }

         deleteShaders();
      }
   } else {
      std::cerr << "[ShaderProgramCreator::LinkProgram] Program does not exist!!!\n";
   }
}

bool ShaderProgramCreator::loadCode(GLchar **data, const char *file_name) {

   FILE *input_data = NULL;
   int status;

   if ((input_data = fopen(file_name, "rb")) != NULL) {
      long int size;
      long int i;

      status = fseek(input_data, 0, SEEK_END);
      if (status != 0) {
         fclose(input_data);
         return true;
      }

      size = ftell(input_data);
      if (size < 0) {
         fclose(input_data);
         return true;
      }

      rewind(input_data);

      *data = (GLchar *) malloc(size + 1);
      memset((*data), '\0', size);

      fread((*data), 1, size, input_data);
      (*data)[size] = '\0';

      fclose(input_data);
   }
}

void ShaderProgramCreator::deleteShaders() {
   for (auto const &shader : shaders) {
      glDetachShader(shaderProgram, shader->object);
   }

   while (!shaders.empty()) {
      delete shaders.back();
      shaders.pop_back();
   }
}

ShaderProgramCreator::ShaderProgramCreator() {
   shaderProgram = 0;
   error_flag = false;
   link_flag = false;
}

void ShaderProgramCreator::deleteShaderProgram() {
   deleteShaders();
   if (shaderProgram != 0) {
      glDeleteProgram(shaderProgram);
      shaderProgram = 0;
   }
   error_flag = false;
   link_flag = false;
}

ShaderProgramCreator::~ShaderProgramCreator() {
   deleteShaderProgram();
}

