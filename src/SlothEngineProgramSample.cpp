#include <iostream>
#include <algorithm>
#include "SlothEngineProgramSample.h"

void SlothEngineProgramSample::create() {
   inputProcessor = InputProcessor::getInputProcessor();

   camera = new Camera(16 / (float) 9);
   camera->farClip = 1000.f;
   camera->position = glm::vec3(0, 1, 5);
   camera->front = glm::vec3(.0, .0, .0);

   numOfGameObjects = 1;

   Mesh commandoMesh("./../assets/republic.commando/mesh.obj");
   Texture commandoTexture("./../assets/republic.commando/texture.png");
   for (int i = 0; i < numOfGameObjects; i++) {
      commandos.push_back(GameObject(commandoMesh, commandoTexture));
      commandos.back().position.z = 2 * (i - (numOfGameObjects / 2));
      commandos.back().position.x = 3;
   }
}

void SlothEngineProgramSample::update(float deltaTime) {=
   Sloth::cameraRotation = inputProcessor->mouseButtonsState[GLFW_MOUSE_BUTTON_RIGHT];

   timeSinceBeginning += deltaTime;
}

void SlothEngineProgramSample::render(float deltaTime) {
   update(deltaTime);
   glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glUniform3fv(Sloth::phongShader->getUniformLocation("ambientLight"), 1, glm::value_ptr(ambientLight));

   camera->update(deltaTime);

   for (int i = 0; i < numOfGameObjects; i++) {
      commandos[i].draw();
   }

}