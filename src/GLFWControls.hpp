/* GLFWControls.hpp
 * Zarządzanie sterowaniem w GLFW.
 * (C) Jan Bielański 2016
 */

#ifndef __GLFW_CONTROLS_HPP__
#define __GLFW_CONTROLS_HPP__

#include "OpenGL.hpp"

// Obsługa błędów GLFW
void error_callback(int error, const char* description);

// Obsługa klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Obsługa przycisków myszy
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// Obsługa rolki myszy
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Obsługa położenia kursora
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

#endif

