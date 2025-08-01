#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class WindowsManager
{
public:
	WindowsManager(int width, int height, const char* title);
	~WindowsManager();
	bool GLFWInitialize();
	GLFWwindow* GetWindow() const;



private:
	GLFWwindow* window;
	int width;
	int height;
	const char* title;


};
