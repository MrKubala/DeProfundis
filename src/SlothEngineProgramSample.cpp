#include <iostream>
#include "SlothEngineProgramSample.h"


void SlothEngineProgramSample::create() {
   camera = new Camera(16 / (float)9);
   camera->farClip = 1000.f;
   numOfGameObjects = 6;
   Mesh blasterModel("./../assets/BladeRunner_blaster/BladeRunner_blaster.obj");
   Texture blasterTexture("./../assets/BladeRunner_blaster/textures/blaster_albedo.tga");
   for(int i = 0; i < numOfGameObjects; i++){
      blasters.push_back(GameObject(blasterModel, blasterTexture));
      blasters.back().position.z = 2 * (i - (numOfGameObjects/2));
   }
   Mesh commandoModel("./../assets/RepublicCommand/model.obj");
   Texture commandoTexture("./../assets/RepublicCommand/texture.png");
   for(int i = 0; i < numOfGameObjects; i++){
      commandos.push_back(GameObject(commandoModel, commandoTexture));
      commandos.back().position.z = 2 * (i - (numOfGameObjects/2));
      commandos.back().position.x = 3;
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
      commandos[i].draw();
   }
}




