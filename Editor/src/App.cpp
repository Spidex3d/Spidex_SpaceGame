#include "App.h"
#include "../Engine/Engine/Windows/WindowsManager.h"
#include "GUI/MainScreen.h"
#include "GlobalVars.h"

#include "../../Engine/Engine/ECS/EntityNode.h"
#include "../../Engine/Engine/Camera/Camera.h"
#include "../../Engine/Engine/Input/Input.h"
#include "../../Engine/Engine/Shader/ShaderManager.h"
#include "../../Engine/Engine/ECS/DefaultLevel.h"

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


    ShaderManager::SetupShaders(); // Initialize the shaders

    RenderDraw::Instance()->Creat_FrameBuffer(); // my frame buffer to fill main scene window

    EntityNode entityComponents;
    entityComponents.Initialize();

    int index = 0, objectIndex = 0, indexTypeID = 0;

    
    while (AppIsRunning) {
        
        App::Instance()->Timer();

        if (glfwWindowShouldClose(windowManager.GetWindow())) {
            AppIsRunning = false;
        }

        CubeModel* playerCube = entityComponents.GetPlayerCube(entityComponents.GetModels(), PlayerIdx);
        

        processPlayerMovement(windowManager.GetWindow(), playerCube, deltaTime);

        // Camera follow logic
        if (playerCube) {
            glm::mat4 rotMatrix = glm::mat4(1.0f);
            rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.y, glm::vec3(0, 1, 0)); // Yaw
            rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.x, glm::vec3(1, 0, 0)); // Pitch
            rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.z, glm::vec3(0, 0, 1)); // Roll

            glm::vec3 forward = glm::vec3(rotMatrix * glm::vec4(0, 0, -1, 0));
            glm::vec3 up = glm::vec3(rotMatrix * glm::vec4(0, 1, 0, 0));
            glm::vec3 desiredCameraPos = playerCube->position - forward * 10.0f + up * 3.0f;

            // Optional: smooth the camera movement
            camera.Position = glm::mix(camera.Position, desiredCameraPos, 0.1f);

            camera.Front = glm::normalize(playerCube->position - camera.Position);
            camera.updateCameraVectors();
        }
  //      
		processInput(windowManager.GetWindow()); // Process input events

		MainScreen::Instance()->WinInit(windowManager.GetWindow()); // new imgui frame, menu and dockspace
       
        MainScreen::Instance()->MainSceneWindow(windowManager.GetWindow()); // This is the main imgui drawing window for the editor

        EntityNode::Instance()->EntityManagmentSystem(entityComponents.GetModels(), currentIndex,
            index, objectIndex, indexTypeID); // Entity Management System Scene list

		DefaultLevel::Instance()->LevelEditorWindow(); // Default Level Editor Window
        
        // ############################################# Camera Object !!! ################################

        RenderDraw::Instance()->Bind_Framebuffer(); // for the main screen

        MainScreen::Instance()->BgColor(BgCol);
		MainScreen::Instance()->ClearScreen(); // Clear the screen

        App::MainCamera(); // ########## This is the main Camera ##########
        // Render the grid and then have a coffee
        if (!gridNogrid) {   // Show the grid or hide it
            EntityNode::Instance()->RenderGrid(camera.GetViewMatrix(),
                camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT),
                entityComponents.GetModels(), currentIndex, Gridobjidx);
			
        }

        // TODO: Editor/game logic and rendering here
        // Darw all objects on screen
        EntityNode::Instance()->RenderScene(camera.GetViewMatrix(),
            camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT),
            entityComponents.GetModels(), currentIndex, *ShaderManager::defaultGridShader, camera);

        RenderDraw::Instance()->Unbinde_Frambuffer();

        MainScreen::Instance()->RenderImGui(windowManager.GetWindow());

		glfwSwapBuffers(windowManager.GetWindow()); // Swap buffers to display the rendered frame
		glfwPollEvents(); // Poll for and process events
  
		
    }

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

void App::Timer()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame; // Calculate the time difference between the current frame and the last frame
	lastFrame = currentFrame; // Update the last frame time
}

App::~App()
{
}
