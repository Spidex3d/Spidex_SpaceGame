#include "App.h"
#include "../../Engine/Engine/Engine.h"
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
    Engine engine;
    if (!engine.Init(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE)) {
        return;
    }
    MainScreen::Instance()->Initialize(window);  //##########


    GLFWwindow* window = engine.GetWindow();

    MainScreen::Instance()->SetUpImGui(window);

    ShaderManager::SetupShaders(); // Initialize the shaders

    RenderDraw::Instance()->Creat_FrameBuffer(); // my frame buffer to fill main scene window

    EntityNode entityComponents;
    entityComponents.Initialize();

    int index = 0, objectIndex = 0, indexTypeID = 0;

    while (!engine.ShouldClose()) {
        engine.PollEvents();
        engine.BeginFrame();

		MainScreen::Instance()->WinInit(window); // new imgui frame, menu and dockspace
       // MainScreen::Instance()->WinInit(windowManager.GetWindow()); // Initialize all the above

        MainScreen::Instance()->MainSceneWindow(window); // This is the main imgui drawing window for the editor
        

		processInput(window); // Process input events

        EntityNode::Instance()->EntityManagmentSystem(entityComponents.GetModels(), currentIndex,
            index, objectIndex, indexTypeID); // Entity Management System Scene list

        
        // ############################################# Camera Object !!! ################################
        App::MainCamera(); // ########## This is the main Camera ##########

        RenderDraw::Instance()->Bind_Framebuffer(); // for the main screen

        // TODO: Editor/game logic and rendering here
        // Render the grid and then have a coffee
        if (!gridNogrid) {   // Show the grid or hide it
            EntityNode::Instance()->RenderGrid(camera.GetViewMatrix(),
                camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT),
                entityComponents.GetModels(), currentIndex, Gridobjidx);
			
        }

        RenderDraw::Instance()->Unbinde_Frambuffer();
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
