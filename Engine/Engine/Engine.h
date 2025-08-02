#pragma once
#include "Windows/WindowsManager.h"

class Engine
{
public:
    Engine();
    ~Engine();

    GLFWwindow* GetWindow() const;

    bool Init(int width, int height, const char* title);
    void PollEvents();
    void BeginFrame();
    void EndFrame();
    bool ShouldClose();
    void Shutdown();

private:
    WindowsManager* windowManager;
	

};

