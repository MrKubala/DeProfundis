//
// Created by Kuba on 2016-05-03.
//

#ifndef DEPROFUNDIS_INPUTPROCESSOR_H
#define DEPROFUNDIS_INPUTPROCESSOR_H


#include "OpenGL.hpp"

class InputProcessor {
public:
   bool *inputState;
   double mouseXPos, mouseYPos, mouseLastXPos, mouseLastYPos;

   static InputProcessor &getInputProcessor() {
      static InputProcessor inputProcessor;
      return inputProcessor;
   }

   void update();

   void handleKeyPressed(int key);

   void handleKeyReleased(int key);

   void handleMouseMovement(double xPos, double yPos);
   double getMouseXOffset(){ return mouseXPos - mouseLastXPos;}
   double getMouseYOffset(){ return mouseLastYPos - mouseYPos ;}

   ~InputProcessor() { delete[] inputState; }

private:
   int maxInputNumber = GLFW_KEY_LAST + 1;
   InputProcessor() : mouseXPos(0), mouseYPos(0), mouseLastXPos(0), mouseLastYPos(0) {
      inputState = new bool[maxInputNumber];
      for (int i = 0; i < maxInputNumber; i++) { inputState[i] = false; }
   }

   void resetMouseOffset();
};


#endif //DEPROFUNDIS_INPUTPROCESSOR_H
