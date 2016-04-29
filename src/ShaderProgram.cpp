/* ShaderProgram.cpp
 * Biblioteka udostępnia klasę umozliwiającą łatwe zarządzanie
 * programami shaderów.
 *
 *
 * (C) Jan Bielański 2016
 */

#include "ShaderProgram.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>


// [ShaderObject] Usuwanie shadera
void ShaderObject::Remove() {
  if(object != 0) { glDeleteShader(object); }
  type = 0;
  object = 0;
}

// [ShaderObject] Konstruktor
ShaderObject::ShaderObject(GLuint shader_type) {
  type = shader_type;
  object = 0;
}

// [ShaderObject] Destruktor
ShaderObject::~ShaderObject() {
  if(object != 0) { glDeleteShader(object); }
}

// [ShaderProgram] Dodawanie shadera - zródła shadera w tablicy
void ShaderProgram::AddShaderWithSources(GLuint shader_type, const char *shader_code) {

  // Tworzenie nowego obiektu
  shaders.push_back(new ShaderObject(shader_type));

  // Tworzenie shadera
  shaders.back()->object = glCreateShader(shaders.back()->type);

  // Testowanie porawności
  if(shaders.back()->object != 0) {
    
    //Dołaczenie kodu shadera
    glShaderSource(shaders.back()->object, 1, &shader_code, NULL);

    //Kompilacja shadera
    glCompileShader(shaders.back()->object);

    GLint shader_status;
    glGetShaderiv(shaders.back()->object,GL_COMPILE_STATUS,&shader_status);
    if(shader_status != GL_TRUE) {
      std::cerr<<"[ShaderProgram::AddShaderWithSources] Can not compile shader object!!!\n";
      error_flag = true;
    }
  } else {
    std::cerr<<"[ShaderProgram::AddShaderWithSources] Can not create shader object!!!\n";
    error_flag = true;
  }

  // Wykonywanie operacji dla kodu błędu
  if(error_flag) {
    delete shaders.back();
    shaders.pop_back();
    error_flag = false;
  }
}

// [ShaderProgram] Dodawanie shadera - zródła shadera w pliku
void ShaderProgram::AddShaderFromFile(GLuint shader_type, const char *file_name) {

  // Tworzenie nowego obiektu
  shaders.push_back(new ShaderObject(shader_type));

  // Tworzenie shadera
  shaders.back()->object = glCreateShader(shaders.back()->type);

  // Testowanie porawności
  if(shaders.back()->object != 0) {

    // Dane shadera
    GLchar *data = nullptr;

    // Wczytanie kodu shadera
    error_flag = LoadCode(&data,file_name);

    // Kompilacja shadera
    if(data != nullptr || error_flag) {

      //Dołaczenie kodu shadera
      glShaderSource(shaders.back()->object, 1, const_cast<const GLchar **>(&data), NULL);

      //Kompilacja shadera
      glCompileShader(shaders.back()->object);

      GLint shader_status;
      glGetShaderiv(shaders.back()->object,GL_COMPILE_STATUS,&shader_status);
      if(shader_status != GL_TRUE) {
	std::cerr<<"[ShaderProgram::AddShaderFromFile] Can not compile shader object!!!\n";
	error_flag = true;
      }

      // Usunięcie kodu
      free(data);
      
    } else {
      std::cerr<<"[ShaderProgram::AddShaderFromFile] Shader source code does not exist!!!\n";
      error_flag = true;
    }
  } else {
    std::cerr<<"[ShaderProgram::AddShaderFromFile] Can not create shader object!!!\n";
    error_flag = true;
  }

  // Wykonywanie operacji dla kodu błędu
  if(error_flag) {
    delete shaders.back();
    shaders.pop_back();
    error_flag = false;
  }
}

// [ShaderProgram] Linkowanie programu
void ShaderProgram::Link() {
  
  // Tworzenie programu
  if(program == 0) {
    program = glCreateProgram();
  }

  // Linkowanie programu
  if(glIsProgram(program)) {
    if(!link_flag) {
      GLuint types[6] = {GL_VERTEX_SHADER,GL_TESS_CONTROL_SHADER,GL_TESS_EVALUATION_SHADER,GL_GEOMETRY_SHADER,GL_FRAGMENT_SHADER,GL_COMPUTE_SHADER};

      // Dołączanie shadera do programu
      for(auto const &t : types) {
	for(auto const &shader : shaders) {
	  if(shader->type == t) {
	    glAttachShader(program,shader->object);
	  }
	}
      }

      // Linkowanie programu
      if(!link_flag) {
	glLinkProgram(program);
	link_flag = true;
      }

      // Odlinkowanie i usuwanie shaderów
      DeleteShaders();
    }
  } else {
    std::cerr<<"[ShaderProgram::LinkProgram] Program does not exist!!!\n";
  }
}

// [ShaderProgram] Wykorzystanie programu
void ShaderProgram::Use() {
  switch(link_flag) {
  case true:
    glUseProgram(program);
    break;
  default:
    std::cerr<<"[ShaderProgram::UseProgram] Program does not linked!!!\n";
    break;
  };
}

// [ShaderProgram] Usuwanie programu i shaderow
void ShaderProgram::Delete() {
  DeleteShaders();
  if(program != 0) {
    glDeleteProgram(program);
    program = 0;
  }
  error_flag = false;
  link_flag = false;
}

// [ShaderProgram] Pobranie programu
GLuint ShaderProgram::Get() {
  return program;
}
// [ShaderProgram [private]] Ładowanie kodu źródłowego
bool ShaderProgram::LoadCode(GLchar **data, const char *file_name) {

  FILE *input_data = NULL; int status;

  if((input_data = fopen(file_name,"rb")) != NULL) {
    long int size; long int i;
    
    //Wyszukanie końca pliku
    status = fseek(input_data,0,SEEK_END);
    if(status != 0) {
      fclose(input_data);
      return true;
    }

    //Odczytanie długości pliku
    size = ftell(input_data);
    if(size < 0) {
      fclose(input_data);
      return true;
    }

    //Powrót do początku pliku
    rewind(input_data);

    //Alokacja pamięci na dane z pliku i zerowanie tablicy
    *data = (GLchar*) malloc(size + 1);
    memset((*data),'\0',size);

    //Odczytanie danych z pliku
    fread((*data),1,size,input_data);
    (*data)[size] = '\0';

    //Zamknięcie pliku
    fclose(input_data);
  }
}

// [ShaderProgram [private]] Usuwanie shaderów
void ShaderProgram::DeleteShaders() {
  // Odlinkowanie shaderów
  for(auto const &shader : shaders) {
    glDetachShader(program,shader->object);
  }

  // Usuwanie shaderów
  while(!shaders.empty()) {
    delete shaders.back();
    shaders.pop_back();
  }	
}

// [ShaderProgram] Konstruktor
ShaderProgram::ShaderProgram() {
  program = 0;
  error_flag = false;
  link_flag = false;
}

// [ShaderProgram] Destruktor
ShaderProgram::~ShaderProgram() {
  Delete();
}

