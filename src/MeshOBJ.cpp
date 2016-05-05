#include <cstdio>
#include <cstring>
#include <glm/vec2.hpp>
#include <string>
#include "MeshOBJ.h"

void Mesh::loadOBJ(const char *path) {
   std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
   std::vector<glm::vec3> temp_vertices;
   std::vector<glm::vec2> temp_uvs;
   std::vector<glm::vec3> temp_normals;

   FILE *objFile = openFile(path);

   char line[512];
   while (1) {
      int response = fscanf(objFile, "%s", line);
      if (response == EOF) {
         break;
      }

      if (strcmp(line, "v") == 0) {
         glm::vec3 vertex;
         fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
         temp_vertices.push_back(vertex);
      } else if (strcmp(line, "vt") == 0) {
         glm::vec2 uv;
         fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
         uv.y = -uv.y;
         temp_uvs.push_back(uv);
      } else if (strcmp(line, "vn") == 0) {
         glm::vec3 normal;
         fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
         temp_normals.push_back(normal);
      } else if (strcmp(line, "f") == 0) {
         unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
         int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                              &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2],
                              &normalIndex[2]);
         if (matches != 9) {
            printf("File can't be read by OBJ loader.\n");
            break;
         }
         vertexIndices.push_back(vertexIndex[0]);
         vertexIndices.push_back(vertexIndex[1]);
         vertexIndices.push_back(vertexIndex[2]);
         uvIndices.push_back(uvIndex[0]);
         uvIndices.push_back(uvIndex[1]);
         uvIndices.push_back(uvIndex[2]);
         normalIndices.push_back(normalIndex[0]);
         normalIndices.push_back(normalIndex[1]);
         normalIndices.push_back(normalIndex[2]);
      }
   }
   processOBJData(vertexIndices, uvIndices, normalIndices, temp_vertices, temp_uvs, temp_normals);
}

void Mesh::processOBJData(std::vector<unsigned int> vertexIndices,
                    std::vector<unsigned int> uvIndices,
                    std::vector<unsigned int> normalIndices,
                    std::vector<glm::vec3> temp_vertices,
                    std::vector<glm::vec2> temp_uvs,
                    std::vector<glm::vec3> temp_normals){

   for( unsigned int i=0; i<vertexIndices.size(); i++ ){

      // Get the indices of its attributes
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int uvIndex = uvIndices[i];
      unsigned int normalIndex = normalIndices[i];

      // Get the attributes thanks to the index
      glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
      glm::vec2 uv = temp_uvs[ uvIndex-1 ];
      glm::vec3 normal = temp_normals[ normalIndex-1 ];

      // Put the attributes in buffers
      vertices.push_back(vertex);
      uvs     .push_back(uv);
      normals .push_back(normal);

   }

}

FILE *Mesh::openFile(const char *path) {
   FILE *file = fopen(path, "r");
   if (file == NULL) {
      printf("Error at opening file.\n");
      return nullptr;
   }
   return file;
}