#include "App.h"
#include "../../Engine/Engine/Engine.h"
#include "GUI/MainScreen.h"
#include "GlobalVars.h"
#include "ECS\EntityNode.h"

App::App()
{
}

App* App::Instance()
{
	App* mainApp = new App;
	return mainApp;
}

void App::Initialize(GLFWwindow* window)
{
}

void App::RunApp()
{
    Engine engine;
    if (!engine.Init(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE)) {
        return;
    }
    GLFWwindow* window = engine.GetWindow();

    MainScreen::Instance()->SetUpImGui(window);

    EntityNode entityComponents;
    entityComponents.Initialize();
    int index = 0, objectIndex = 0, indexTypeID = 0;
    while (!engine.ShouldClose()) {
        engine.PollEvents();
        engine.BeginFrame();

        MainScreen::Instance()->WinInit(window);

        MainScreen::Instance()->MainSceneWindow(window); // main drawing window

        EntityNode::Instance()->EntityManagmentSystem(entityComponents.GetModels(), currentIndex,
            index, objectIndex, indexTypeID); // Entity Management System Scene list

        // TODO: Editor/game logic and rendering here

        MainScreen::Instance()->RenderImGui(window);

        engine.EndFrame();
    }

    engine.Shutdown();
	AppShutdown();
    
}

void App::AppShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

App::~App()
{
}
