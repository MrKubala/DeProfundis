#include <iostream>
#include <algorithm>
#include "SlothEngineProgramSample.h"

void SlothEngineProgramSample::create() {
   atb = &ATB::getInstanse();
   atb->init();

   inputProcessor = InputProcessor::getInputProcessor();

   Sloth::lightsObjects = &lightsObjects;
   camera = new Camera(16 / (float) 9);
   camera->farClip = 1000.f;
   camera->position = glm::vec3(0, 1, 5);
   camera->front = glm::vec3(.0, .0, .0);

   modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

#ifdef MANY_OBJECTS_DEMO
   numOfGameObjects = 6;
   Mesh blasterMesh("./../assets/blade.runner.blaster/mesh.obj");
   Texture blasterTexture("./../assets/blade.runner.blaster/texture.tga");
   for(int i = 0; i < numOfGameObjects; i++){
      blasters.push_back(GameObject(blasterMesh, blasterTexture));
      blasters.back().position.z = 2 * (i - (numOfGameObjects/2));
   }
   Mesh commandoMesh("./../assets/republic.commando/mesh.obj");
   Texture commandoTexture("./../assets/republic.commando/texture.png");
   for(int i = 0; i < numOfGameObjects; i++){
      commandos.push_back(GameObject(commandoMesh, commandoTexture));
      commandos.back().position.z = 2 * (i - (numOfGameObjects/2));
      commandos.back().position.x = 3;
   }

   Mesh knightMesh("./../assets/knight/mesh.obj");
   Texture knightTexture("./../assets/knight/texture.jpg");
   knights.push_back(GameObject(knightMesh, knightTexture));
   knights.back().position.y = 5;
#else
   Mesh cubeMesh("./../assets/cube/mesh.obj");
   Texture cubeTexture("./../assets/cube/texture.jpg");
   cubeModel = new GameObject(cubeMesh, cubeTexture);

   Mesh commandoMesh("./../assets/republic.commando/mesh.obj");
   Texture commandoTexture("./../assets/republic.commando/texture.png");
   commandoModel = new GameObject(commandoMesh, commandoTexture);

   Mesh blasterMesh("./../assets/blade.runner.blaster/mesh.obj");
   Texture blasterTexture("./../assets/blade.runner.blaster/texture.tga");
   blasterModel = new GameObject(blasterMesh, blasterTexture);

   Mesh knightMesh("./../assets/knight/mesh.obj");
   Texture knightTexture("./../assets/knight/texture.jpg");
   knightModel = new GameObject(knightMesh, knightTexture);
#endif

   Mesh lightCubeMesh("./../assets/cube/mesh.obj");
   Texture whiteTexture("./../assets/cube/white.jpg");
   lightCube = new GameObject(lightCubeMesh, whiteTexture);
   lightingManager = &LightingManager::get();

   directionalLight.position = glm::vec4(600.0f, 100.0f, -30.0f, 0.0f);
   directionalLight.color = glm::vec3(1.0f, 0.90f, 0.7f);
   directionalLight.color *= 0.6f;
   lightingManager->addLight(&directionalLight);
   atb->addLightBar(&directionalLight);

   dynamicLight.position = glm::vec4(6.0f, 1.0f, 0.0f, 1.0f);
   dynamicLight.color = glm::vec3(0.0f, 0.0f, 0.0f);
   dynamicLight.attenuation = 0.01f;
   lightingManager->addLight(&dynamicLight);
   atb->addLightBar(&dynamicLight);

   setMainATBBar();
}

void SlothEngineProgramSample::update(float deltaTime) {
   if (inputProcessor->inputState[GLFW_KEY_MINUS]) {
      atb->hideAllBars();
   }
   if (inputProcessor->inputState[GLFW_KEY_EQUAL]) {
      atb->showAllBars();
   }
   if (!inputProcessor->inputState[GLFW_KEY_1]) {
      canToggleMainBar = true;
   }
   if (canToggleMainBar && inputProcessor->inputState[GLFW_KEY_F1]) {
      atb->toggleMainBarVisibility();
      canToggleMainBar = false;
   }

   timeSinceBeginning += deltaTime;
   float x = glm::sin(timeSinceBeginning) * lightsMinRadius;
   float z = glm::cos(timeSinceBeginning) * lightsMinRadius;
   dynamicLight.position.x = x;
   dynamicLight.position.z = z;
   float r = glm::sin(timeSinceBeginning * 9);
   r = glm::abs(r);
   dynamicLight.color.r = r;
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

#ifdef MANY_OBJECTS_DEMO
   for(int i = 0; i < numOfGameObjects; i++){
      blasters[i].draw();
      commandos[i].draw();
   }
   for(int i = 0; i< knights.size(); i++){
      knights[i].draw();
   }
#else
   switch (m_currentMesh) {
      case CUBE:
         cubeModel->position = modelPosition;
         cubeModel->rotation = modelRotation;
         cubeModel->scale = modelScale;
         cubeModel->draw();
         break;
      case COMMANDO:
         commandoModel->position = modelPosition;
         commandoModel->rotation = modelRotation;
         commandoModel->scale = modelScale;
         commandoModel->draw();
         break;
      case BLASTER:
         blasterModel->position = modelPosition;
         blasterModel->rotation = modelRotation;
         blasterModel->scale = modelScale;
         blasterModel->draw();
         break;
      case KNIGHT:
         knightModel->position = modelPosition;
         knightModel->rotation = modelRotation;
         knightModel->scale = modelScale;
         knightModel->draw();
         break;
   }
#endif

   for (int i = 0; i < lightingManager->numberOfLights; i++) {
      lightCube->position.x = lightingManager->lights[i]->position.x;
      lightCube->position.y = lightingManager->lights[i]->position.y;
      lightCube->position.z = lightingManager->lights[i]->position.z;
      lightCube->draw();
   }

   atb->draw();
}

//for showcase purposes


float random() {
   return ((float) rand() / RAND_MAX);
}

void TW_CALL addMoreLightsTWCall(void *data) {
   Sloth::lightsObjects->push_back(Light());

   Sloth::lightsObjects->back().position.x = (random() * 20) - 10;
   Sloth::lightsObjects->back().position.y = (random() * 20) - 10;
   Sloth::lightsObjects->back().position.z = (random() * 20) - 10;

   Sloth::lightsObjects->back().color.r = random();
   Sloth::lightsObjects->back().color.g = random();
   Sloth::lightsObjects->back().color.b = random();

   LightingManager::get().addLight(&(Sloth::lightsObjects->back()));
   ATB::getInstanse().addLightBar(&Sloth::lightsObjects->back());
}

void SlothEngineProgramSample::setMainATBBar() {
   TwAddVarRW(atb->mainBar, "Position", TW_TYPE_VECTOR3F, (void *) &camera->position, NULL);
   TwAddVarRW(atb->mainBar, "Direction", TW_TYPE_DIR3F, (void *) &camera->front, NULL);
   TwAddSeparator(atb->mainBar, NULL, NULL);
   TwAddVarRW(atb->mainBar, "Ambient Color", TW_TYPE_COLOR3F, (void *) &ambientLightColor, NULL);
   TwAddVarRW(atb->mainBar, "Specular Power", TW_TYPE_FLOAT, (void *) &specularPower, "min=0 step=0.01");
   TwAddVarRW(atb->mainBar, "Specular Intensity", TW_TYPE_FLOAT, (void *) &specularIntensity, "min=0 step=0.01");
   TwAddSeparator(atb->mainBar, NULL, NULL);
   TwAddVarRW(atb->mainBar, "Num of lights", TW_TYPE_INT32, (void *) &lightingManager->numberOfLights, NULL);
   TwAddButton(atb->mainBar, "MOOOREE LIGHTS", addMoreLightsTWCall, NULL, NULL);
   TwAddSeparator(atb->mainBar, NULL, NULL);
   TwAddVarRW(atb->mainBar, "Display as wireframe", TW_TYPE_BOOL32, (void *) &Sloth::displayAsWireframe, NULL);
   TwAddSeparator(atb->mainBar, NULL, NULL);

   TwEnumVal Meshes[] = {{CUBE,     "Companion cube"},
                         {COMMANDO, "Republic Commando"},
                         {BLASTER,  "Deckards blaster"},
                         {KNIGHT,   "Common fantasy knight"}};
   TwType MeshTwType = TwDefineEnum("MeshType", Meshes, 4);
   TwAddVarRW(atb->mainBar, "Model", MeshTwType, &m_currentMesh, NULL);
   TwAddVarRW(atb->mainBar, "Model position", TW_TYPE_VECTOR3F, (void *) &modelPosition, NULL);
   TwAddVarRW(atb->mainBar, "Model rotation", TW_TYPE_VECTOR3F, (void *) &modelRotation, NULL);
   TwAddVarRW(atb->mainBar, "Model scale", TW_TYPE_VECTOR3F, (void *) &modelScale, NULL);


}

