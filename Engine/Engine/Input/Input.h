#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "../Camera/Camera.h"


extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;
extern bool mouse;
extern float deltaTime;
extern float lastFrame;
extern float fov;



//void processInput(GLFWwindow* window, Camera& camera);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

