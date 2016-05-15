#include <iostream>
#include "SlothEngineProgramSample.h"


void SlothEngineProgramSample::create() {
   camera = new Camera(16 / (float)9);
   camera->farClip = 1000.f;
   numOfGameObjects = 100;
   Mesh mesh("./../assets/BladeRunner_blaster/BladeRunner_blaster.obj");
   Texture texture("./../assets/BladeRunner_blaster/textures/blaster_albedo.tga");
   for(int i = 0; i < numOfGameObjects; i++){
      blasters.push_back(GameObject(mesh, texture));
      blasters.back().position.z = 2 * (i - (numOfGameObjects/2));
   }
}

void SlothEngineProgramSample::update(float deltaTime) {
}

void SlothEngineProgramSample::render(float deltaTime) {
   glClearColor(0.4f, 0.6f, 0.6f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   update(deltaTime);
   camera->update(deltaTime);
   for(int i = 0; i < numOfGameObjects; i++){
      blasters[i].draw();
   }
}




