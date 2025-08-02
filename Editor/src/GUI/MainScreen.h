#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui\ImGuiAF.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

class MainScreen
{
public:
	static MainScreen* Instance();
	void Initialize(GLFWwindow* window);

	void SetUpImGui(GLFWwindow* window);      // imgui set up
	void NewImGuiFrame(GLFWwindow* window);   // imgui new frame
	void MainDockSpace(bool* p_open);		  // add docking
	
	void MainMenuBar(GLFWwindow* window);     // main editor menu bar

	void WinInit(GLFWwindow* window);		  // new frame, menu and dockspace

	void RenderImGui(GLFWwindow* window);     // imgui main imgui rendering


private:
	GLFWwindow* window;

	
	
};

