#pragma once
#include "WindowsManager.h"
class Engine
{
public:
    Engine();
    ~Engine();
    bool Init(int width, int height, const char* title);
    void PollEvents();
    void BeginFrame();
    void EndFrame();
    bool ShouldClose();
    void Shutdown();

private:
    WindowsManager* windowManager;

};

