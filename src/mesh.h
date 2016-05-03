#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex
{
public:
   Vertex(const glm::vec3& pos)
   {
      this->pos = pos;
      this->texCoord = texCoord;
   }

   glm::vec3* GetPos() { return &pos; }
   glm::vec2* GetTexCoord() { return &texCoord; }

private:
   glm::vec3 pos;
   glm::vec2 texCoord;
};

enum MeshBufferPositions
{
   POSITION_VB,
   TEXCOORD_VB,
   NORMAL_VB,
   INDEX_VB
};

class Mesh
{
public:
   Mesh(Vertex* vertices, unsigned int numVertices);

   void Draw();

   virtual ~Mesh();
protected:
private:
   static const unsigned int NUM_BUFFERS = 4;
   Mesh(const Mesh& mesh) {}

   GLuint m_vertexArrayObject;
   GLuint m_vertexArrayBuffers[NUM_BUFFERS];
   unsigned int m_drawCount;
};

#endif