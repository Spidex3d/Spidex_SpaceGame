#include "App.h"
#include "../Engine/Engine/Windows/WindowsManager.h"
//#include "../../Engine/Engine/Engine.h"
#include "GUI/MainScreen.h"
#include "GlobalVars.h"

#include "../../Engine/Engine/ECS/EntityNode.h"
#include "../../Engine/Engine/Input/Input.h"
#include "../../Engine/Engine/Camera/Camera.h"
#include "../../Engine/Engine/Shader/ShaderManager.h"

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
	WindowsManager windowManager(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);
	if (!windowManager.GLFWInitialize()) {
		return;
    }
    else
    {
        MainScreen::Instance()->Initialize(windowManager.GetWindow());  //##########
		glfwSetCursorPosCallback(windowManager.GetWindow(), mouse_callback);
		glfwSetScrollCallback(windowManager.GetWindow(), scroll_callback);
        MainScreen::Instance()->SetUpImGui(windowManager.GetWindow());
    }

    //Engine engine;
    //if (!engine.Init(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE)) {
    //    return;
    //}
    //MainScreen::Instance()->Initialize(window);  //##########


    //GLFWwindow* window = engine.GetWindow();

    //MainScreen::Instance()->SetUpImGui(window);

    ShaderManager::SetupShaders(); // Initialize the shaders

    RenderDraw::Instance()->Creat_FrameBuffer(); // my frame buffer to fill main scene window

    EntityNode entityComponents;
    entityComponents.Initialize();

    int index = 0, objectIndex = 0, indexTypeID = 0;

    // while (!engine.ShouldClose()) {
    while (AppIsRunning) {
        //engine.PollEvents();
        //engine.BeginFrame();

        // Timer

		if (glfwWindowShouldClose(windowManager.GetWindow())) {
			AppIsRunning = false; // Exit the loop if the window should close
		}
		processInput(windowManager.GetWindow()); // Process input events

		MainScreen::Instance()->WinInit(windowManager.GetWindow()); // new imgui frame, menu and dockspace
       // MainScreen::Instance()->WinInit(windowManager.GetWindow()); // Initialize all the above

        MainScreen::Instance()->MainSceneWindow(windowManager.GetWindow()); // This is the main imgui drawing window for the editor
        


        EntityNode::Instance()->EntityManagmentSystem(entityComponents.GetModels(), currentIndex,
            index, objectIndex, indexTypeID); // Entity Management System Scene list

        
        // ############################################# Camera Object !!! ################################

        RenderDraw::Instance()->Bind_Framebuffer(); // for the main screen

        MainScreen::Instance()->BgColor(BgCol);
		MainScreen::Instance()->ClearScreen(); // Clear the screen

        App::MainCamera(); // ########## This is the main Camera ##########
        // TODO: Editor/game logic and rendering here
        // Render the grid and then have a coffee
        if (!gridNogrid) {   // Show the grid or hide it
            EntityNode::Instance()->RenderGrid(camera.GetViewMatrix(),
                camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT),
                entityComponents.GetModels(), currentIndex, Gridobjidx);
			
        }

        RenderDraw::Instance()->Unbinde_Frambuffer();

        MainScreen::Instance()->RenderImGui(windowManager.GetWindow());

		glfwSwapBuffers(windowManager.GetWindow()); // Swap buffers to display the rendered frame
		glfwPollEvents(); // Poll for and process events
  
		
       // engine.EndFrame();
    }

   // engine.Shutdown();
	AppShutdown();
    
}

void App::AppShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void App::MainCamera()
{
    viewMatrix = camera.GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.3f, 200.0f);
}

glm::mat4 App::GetViewMatrix()
{
    return viewMatrix;
}

glm::mat4 App::GetProjectionMatrix(float aspectRatio)
{
    return projectionMatrix;
}

App::~App()
{
}
