#include "GameObject.h"

GameObject::GameObject(Mesh &passedMesh, Texture &passedTexture) : mesh(passedMesh), texture(passedTexture), scale(glm::vec3(1,1,1)){
   mesh = passedMesh;
   texture = passedTexture;
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   GLuint VBO;
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(glm::vec3), &mesh.vertices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
   glEnableVertexAttribArray(0);

   GLuint UVbuffer;
   glGenBuffers(1, &UVbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, UVbuffer);
   glBufferData(GL_ARRAY_BUFFER, mesh.uvs.size() * sizeof(glm::vec2), &mesh.uvs[0], GL_STATIC_DRAW);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
   glEnableVertexAttribArray(1);

   glBindTexture(GL_TEXTURE_2D, texture.texture);

   glBindVertexArray(0);
}

void GameObject::draw() {
   modelMatrixLocation = (*Sloth::shaderProgram).modelMatrixUniformLocation;

   modelMatrix = glm::mat4();
   modelMatrix = glm::translate(modelMatrix, position);
   modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1,0,0));
   modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0,1,0));
   modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0,0,1));
   modelMatrix = glm::scale(modelMatrix, scale);

   glBindVertexArray(VAO);

   glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

   glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());

   glBindVertexArray(0);
}

