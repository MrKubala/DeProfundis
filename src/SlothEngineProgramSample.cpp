#include "SlothEngineProgramSample.h"

void SlothEngineProgramSample::create() {
   atb.init();
   camera = new Camera(16 / (float)9);
   camera->farClip = 1000.f;
   camera->position = glm::vec3(6, 4, 0);
   camera->front = glm::vec3(.0, .0, .0);
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

   Mesh cubeMesh("./../assets/Cube/cube.obj");
   cube = new GameObject(cubeMesh, commandoTexture);

   Mesh knightMesh("./../assets/knight/knight.obj");
   Texture knightTexture("./../assets/knight/knight.jpg");
   knights.push_back(GameObject(knightMesh, knightTexture));
   knights.back().position.y = 5;

   lightingManager = &LightingManager::get();
   directionalLight.position = glm::vec4(600.0f, 100.0f, -30.0f, 0.0f);
   directionalLight.color = glm::vec3(1.0f, 0.90f, 0.7f);
   directionalLight.color *= 0.6f;
   lightingManager->addLight(&directionalLight);
   atb.addLightBar(&directionalLight);

   light1.position = glm::vec4(6.0f, 1.0f, 0.0f, 1.0f);
   light1.color = glm::vec3(0.0f, 0.0f, 0.0f);
   light1.attenuation = 0.01f;

   lightingManager->addLight(&light1);
   atb.addLightBar(&light1);
   setMainATBBar();
}

void SlothEngineProgramSample::update(float deltaTime) {
   timeSinceBeginning += deltaTime;
   float x = glm::sin(timeSinceBeginning) * lightsMinRadius;
   float z = glm::cos(timeSinceBeginning) * lightsMinRadius;
   light1.position.x = x;
   light1.position.z = z;
   float r = glm::sin(timeSinceBeginning * 9);
   r = glm::abs(r);
   light1.color.r = r;
}

void SlothEngineProgramSample::render(float deltaTime) {
   update(deltaTime);
   glClearColor(0.2f, 0.2f, 0.2f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glUniform3fv(Sloth::phongShader->getUniformLocation("ambientLight"), 1, glm::value_ptr(ambientLightColor));
   glUniform1f(Sloth::phongShader->getUniformLocation("materialSpecularPower"), specularPower);
   glUniform1f(Sloth::phongShader->getUniformLocation("materialSpecularIntensity"), specularIntensity);
   lightingManager->processLights();
   camera->update(deltaTime);

   for(int i = 0; i < numOfGameObjects; i++){
      blasters[i].draw();
      commandos[i].draw();
   }

   for(int i = 0; i< knights.size(); i++){
      knights[i].draw();
   }

   for(int i = 0; i < lightingManager->getNumberOfLights(); i++){
      cube->position.x = lightingManager->lights[i]->position.x;
      cube->position.y = lightingManager->lights[i]->position.y;
      cube->position.z = lightingManager->lights[i]->position.z;
      cube->draw();
   }

   atb.draw();
}

void SlothEngineProgramSample::setMainATBBar() {
   TwAddVarRW(atb.mainBar, "Position", TW_TYPE_VECTOR3F, (void*)&camera->position, NULL);
   TwAddVarRW(atb.mainBar, "Ambient Color", TW_TYPE_COLOR3F, (void*)&ambientLightColor, NULL);
}






