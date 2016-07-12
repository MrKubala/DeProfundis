#include <iostream>
#include <algorithm>
#include "SlothEngineProgramSample.h"

void SlothEngineProgramSample::create() {
   inputProcessor = InputProcessor::getInputProcessor();

   camera = new Camera(16 / (float) 9);
   camera->farClip = 1000.f;
   camera->position = glm::vec3(0, 1, 5);
   camera->front = glm::vec3(.0, .0, .0);

   //POKOJ
   Mesh roomMesh("./../assets/Room/Room.obj");
   Texture roomTexture("./../assets/Room/texture.png");
   gameObjects.push_back(GameObject(roomMesh, roomTexture));

   //KANAPA//
   Mesh couchMesh("./../assets/Couch/couch.obj");
   Texture couchTexture("./../assets/Couch/tex.png");
   gameObjects.push_back(GameObject(couchMesh, couchTexture));
   gameObjects.back().scale = glm::vec3(0.013f, 0.013f, 0.013f);
   gameObjects.back().position = glm::vec3(-3.8f, 0.0f, 0.0f);
   gameObjects.back().rotation = glm::vec3(0.0f, 1.57f, 0.0f);

   //LAMPY
   Mesh lamp1Mesh("./../assets/Lamp/lamp.obj");
   Texture lamp1Texture("./../assets/Lamp/tex_green.png");
   gameObjects.push_back(GameObject(lamp1Mesh, lamp1Texture));
   gameObjects.back().position = glm::vec3(2.5f, 2.6f, 1.5f);
   gameObjects.back().scale = glm::vec3(0.6, 0.6f, 0.6f);
   Mesh lamp2Mesh("./../assets/Lamp/lamp.obj");
   Texture lamp2Texture("./../assets/Lamp/tex_green.png");
   gameObjects.push_back(GameObject(lamp2Mesh, lamp2Texture));
   gameObjects.back().position = glm::vec3(-2.5f, 2.6f, 1.5f);
   gameObjects.back().scale = glm::vec3(0.6, 0.6f, 0.6f);
   Mesh lamp3Mesh("./../assets/Lamp/lamp.obj");
   Texture lamp3Texture("./../assets/Lamp/tex_green.png");
   gameObjects.push_back(GameObject(lamp3Mesh, lamp3Texture));
   gameObjects.back().position = glm::vec3(2.5f, 2.6f, -4.5f);
   gameObjects.back().scale = glm::vec3(0.6, 0.6f, 0.6f);
   Mesh lamp4Mesh("./../assets/Lamp/lamp.obj");
   Texture lamp4Texture("./../assets/Lamp/tex_green.png");
   gameObjects.push_back(GameObject(lamp4Mesh, lamp4Texture));
   gameObjects.back().position = glm::vec3(-2.5f, 2.6f, -4.5f);
   gameObjects.back().scale = glm::vec3(0.6, 0.6f, 0.6f);

   //BIURKO
   Mesh deskMesh("./../assets/Desk/desk.obj");
   Texture deskTexture("./../assets/Desk/tex.png");
   gameObjects.push_back(GameObject(deskMesh, deskTexture));
   gameObjects.back().position = glm::vec3(0.6f, 0.0f, -6.2f);
   gameObjects.back().scale = glm::vec3(0.7f, 0.7f, 0.7f);
   gameObjects.back().rotation = glm::vec3(0.0f, 1.57f, 0.0f);

   //BIURKO_LAMPKA
   Mesh deskLampMesh("./../assets/deskLamp/lamp.obj");
   Texture deskLampTexture("./../assets/deskLamp/lamp_d.dds");
   gameObjects.push_back(GameObject(deskLampMesh, deskLampTexture));
   gameObjects.back().position = glm::vec3(0.45f, 0.7f, -5.5f);
   gameObjects.back().scale = glm::vec3(0.3f, 0.3f, 0.3f);
   gameObjects.back().rotation = glm::vec3(0.0f, 2.6f, 0.0f);

   //KRZESLO
   Mesh chairMesh("./../assets/chair/chair.obj");
   Texture chairTexture("./../assets/chair/chair_d.dds");
   gameObjects.push_back(GameObject(chairMesh, chairTexture));
   gameObjects.back().position = glm::vec3(1.6f, 0.0f, -6.2f);
   gameObjects.back().scale = glm::vec3(0.7f, 0.7f, 0.7f);
   gameObjects.back().rotation = glm::vec3(0.0f, -1.1f, 0.0f);

   //KRZESLO
   Mesh tableMesh("./../assets/table/table.obj");
   Texture tableTexture("./../assets/table/tex.png");
   gameObjects.push_back(GameObject(tableMesh, tableTexture));
   gameObjects.back().position = glm::vec3(-1.6f, 0.0f, 0.0f);
   gameObjects.back().scale = glm::vec3(0.8f, 0.8f, 0.8f);
   gameObjects.back().rotation = glm::vec3(0.0f, -1.5f, 0.0f);


}

void SlothEngineProgramSample::update(float deltaTime) {
   Sloth::cameraRotation = inputProcessor->mouseButtonsState[GLFW_MOUSE_BUTTON_RIGHT];

   timeSinceBeginning += deltaTime;
}

void SlothEngineProgramSample::render(float deltaTime) {
   update(deltaTime);
   glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glUniform3fv(Sloth::phongShader->getUniformLocation("ambientLight"), 1, glm::value_ptr(ambientLight));

   camera->update(deltaTime);

   for (int i = 0; i < gameObjects.size(); i++) {
      gameObjects[i].draw();
   }

}