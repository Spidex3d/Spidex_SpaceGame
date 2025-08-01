#include "pch.h"
#include "WindowsManager.h"

WindowsManager::WindowsManager(int width, int height, const char* title)
	: width(width), height(height), title(title), window(nullptr) {}


WindowsManager::~WindowsManager()
{
	if (window)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

bool WindowsManager::GLFWInitialize()
{
	if (!glfwInit())
	{
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Enable vsync	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	return true;
}

GLFWwindow* WindowsManager::GetWindow() const
{
	return window;
}
