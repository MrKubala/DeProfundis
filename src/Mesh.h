#ifndef DEPROFUNDIS_MESH_H
#define DEPROFUNDIS_MESH_H


#include <vector>
#include <glm/vec3.hpp>
#include <wchar.h>

class Mesh {
public:
   std::vector<glm::vec3> vertices;
   std::vector<glm::vec2> uvs;
   std::vector<glm::vec3> normals;

   Mesh(const char *path) { loadOBJ(path); }

   void loadOBJ(const char *path);

private:


   FILE *openFile(const char *path);

   void processOBJData(std::vector<unsigned int> vertexIndices,
                       std::vector<unsigned int> uvIndices,
                       std::vector<unsigned int> normalIndices,
                       std::vector<glm::vec3> temp_vertices,
                       std::vector<glm::vec2> temp_uv,
                       std::vector<glm::vec3> temp_normals);
};


#endif //DEPROFUNDIS_MESH_H
