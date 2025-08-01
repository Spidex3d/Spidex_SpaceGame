#include "../../../Engine/Engine/Engine.h"


int main() {
    Engine engine;
    if (!engine.Init(1280, 720, "Spidex Space Game Editor")) {
        return -1;
    }

    while (!engine.ShouldClose()) {
        engine.PollEvents();
        engine.BeginFrame();

        // TODO: Editor/game logic and rendering here

        engine.EndFrame();
    }

    engine.Shutdown();
    return 0;
}
