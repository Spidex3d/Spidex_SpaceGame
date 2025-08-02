#include "pch.h"
#include "Engine.h"
#include <iostream>

Engine::Engine()
    : windowManager(nullptr) {
}

Engine::~Engine() {
    Shutdown();
}

GLFWwindow* Engine::GetWindow() const  // ############
{
    return windowManager ? windowManager->GetWindow() : nullptr;
}

bool Engine::Init(int width, int height, const char* title) {
    windowManager = new WindowsManager(width, height, title);
    if (!windowManager->GLFWInitialize()) {
        delete windowManager;
        windowManager = nullptr;
        return false;
    }
    else {
	

    return true;

    }

	
}

void Engine::PollEvents() {
    glfwPollEvents();
}

void Engine::BeginFrame() {
    // Prepare for rendering (clear buffers, etc.)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndFrame() {
    if (windowManager && windowManager->GetWindow()) {
        glfwSwapBuffers(windowManager->GetWindow());
    }
}

bool Engine::ShouldClose() {
    return windowManager && windowManager->GetWindow() &&
        glfwWindowShouldClose(windowManager->GetWindow());
}

void Engine::Shutdown() {
    if (windowManager) {
        delete windowManager;
        windowManager = nullptr;
    }
}
