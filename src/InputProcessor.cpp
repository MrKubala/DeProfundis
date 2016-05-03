#include "InputProcessor.h"

void InputProcessor::update() {
   resetMouseOffset();
   glfwPollEvents();
}

void InputProcessor::handleKeyPressed(int key){
   InputProcessor::getInputProcessor().inputState[key] = true;
}
void InputProcessor::handleKeyReleased(int key){
   InputProcessor::getInputProcessor().inputState[key] = false;
}

void InputProcessor::handleMouseMovement(double xPos, double yPos){
   InputProcessor::getInputProcessor().mouseLastXPos = InputProcessor::getInputProcessor().mouseXPos;
   InputProcessor::getInputProcessor().mouseLastYPos = InputProcessor::getInputProcessor().mouseYPos;
   InputProcessor::getInputProcessor().mouseXPos = xPos;
   InputProcessor::getInputProcessor().mouseYPos = yPos;
}


void InputProcessor::resetMouseOffset(){
   InputProcessor::getInputProcessor().mouseLastXPos = InputProcessor::getInputProcessor().mouseXPos;
   InputProcessor::getInputProcessor().mouseLastYPos = InputProcessor::getInputProcessor().mouseYPos;
}