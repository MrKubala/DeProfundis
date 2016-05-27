#ifndef DEPROFUNDIS_INPUTPROCESSOR_H
#define DEPROFUNDIS_INPUTPROCESSOR_H


#include "OpenGL.hpp"

class InputProcessor {
public:
   bool *keyboardKeysState;
   bool *mouseButtonsState;
   double mouseXPos, mouseYPos, mouseLastXPos, mouseLastYPos;

   static InputProcessor *getInputProcessor() {
      static InputProcessor inputProcessor;
      return &inputProcessor;
   }

   void update();

   void handleKeyPressed(int key);

   void handleKeyReleased(int key);

   void handleMouseButtonPressed(int button);

   void handleMouseButtonReleased(int button);

   void handleMouseMovement(double xPos, double yPos);

   double getMouseXOffset();

   double getMouseYOffset();

   static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

   static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

   static void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

   static void mouse_position_callback(GLFWwindow *window, double xpos, double ypos);

   ~InputProcessor() { delete[] keyboardKeysState; }

private:
   int maxKeyboardKeys = GLFW_KEY_LAST;
   int maxMouseButtons = GLFW_MOUSE_BUTTON_LAST;

   InputProcessor() : mouseXPos(0), mouseYPos(0), mouseLastXPos(0), mouseLastYPos(0) {
      keyboardKeysState = new bool[maxKeyboardKeys];
      mouseButtonsState = new bool[maxMouseButtons];
      for (int i = 0; i < maxKeyboardKeys; i++) { keyboardKeysState[i] = false; }
      for (int i = 0; i < maxMouseButtons; i++) { mouseButtonsState[i] = false; }
   }

   void resetMouseOffset();
};


#endif //DEPROFUNDIS_INPUTPROCESSOR_H
