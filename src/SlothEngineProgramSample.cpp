#include <iostream>
#include "SlothEngineProgramSample.h"


void SlothEngineProgramSample::create() {
   camera = new Camera(16 / (float)9);
   blaster = new GameObject(Mesh("./../assets/BladeRunner_blaster/BladeRunner_blaster.obj"), Texture("./../assets/BladeRunner_blaster/textures/blaster_albedo.tga"));
}

void SlothEngineProgramSample::update(float deltaTime) {
}

void SlothEngineProgramSample::render(float deltaTime) {
   glClearColor(0.4f, 0.6f, 0.6f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   update(deltaTime);
   camera->update(deltaTime);
   blaster->draw();
}




