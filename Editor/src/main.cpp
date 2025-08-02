#include "../../Engine/Engine/Engine.h"
#include "GUI/MainScreen.h"


int main() {
    Engine engine;
    if (!engine.Init(1280, 720, "Spidex Space Game Editor")) {
        return -1;
    }
    GLFWwindow* window = engine.GetWindow();

    MainScreen::Instance()->SetUpImGui(window);

    while (!engine.ShouldClose()) {
        engine.PollEvents();
        engine.BeginFrame();

        MainScreen::Instance()->WinInit(window);

        // TODO: Editor/game logic and rendering here

		MainScreen::Instance()->RenderImGui(window);

        engine.EndFrame();
    }

    engine.Shutdown();
    return 0;
}
