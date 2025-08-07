#include "MainScreen.h"
#include <imgui\ImGuiAF.h>
#include "../Editor/src/GlobalVars.h"
#include "../../Engine/Engine/Engine.h"
#include "../../Engine/Engine/Render/RenderDraw.h"
MainScreen* MainScreen::Instance()
{
	static MainScreen* screen = new MainScreen;
	return screen;
}

void MainScreen::Initialize(GLFWwindow* window)
{
}

void MainScreen::SetUpImGui(GLFWwindow* window)
{
    // Make sue to include all imgui files in the project
    //ImGui set up
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    //io.KeyMap[ImGuiKey_H] = GLFW_KEY_HOME;
    ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init("#version 460");
    ImGui_ImplGlfw_InitForOpenGL(window, true);


    // Make it possible to use Icons From FontAwesome5
    ImFontConfig fontconfig;
    fontconfig.MergeMode = true;
    fontconfig.PixelSnapH = true;
    static const ImWchar ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

    // set the fonts
    fontconfig.GlyphOffset = ImVec2(0.0f, 1.0f);
    //io.Fonts->AddFontFromFileTTF(ROBOTO_REG_PATH, FONT_SIZE); // sandard font type
    io.Fonts->AddFontFromFileTTF(FONT_PATH_MAIN, FONT_SIZE); // comic sans font type
    io.Fonts->AddFontFromFileTTF(FA_SOLID_PATH, FONT_SIZE, &fontconfig, ranges);
}

void MainScreen::NewImGuiFrame(GLFWwindow* window)
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

}
// Docking Space
bool DocOnOff = true; // make this a menu item or settings
void MainScreen::MainDockSpace(bool* p_open)
{
    if (DocOnOff) { // Docking on or off
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;// I changed this so my scean shows up on start up

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); // you can add a bit of padding  
        ImGui::Begin("DockSpace Demo", p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);


        // Submit the DockSpace to the ini file
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End();
    }
}

void MainScreen::MainSceneWindow(GLFWwindow* window)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 12));
    ImGui::Begin("Main scene");

    // ##
    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;

    //Rescale_frambuffer(window_width, window_height);
    glViewport(0, 0, window_width, window_height);

    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage((void*)main_scene_texture_id, ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height), ImVec2(0, 1), ImVec2(1, 0));
    // Detect right-click for popup menu 
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        ImGui::OpenPopup("RightClickMenu");
    }
    // Create the right-click popup menu 
    if (ImGui::BeginPopup("RightClickMenu"))
    {
        if (ImGui::BeginMenu("Add New Space")) {
            if (ImGui::MenuItem("Add Star field")) {   
             // this will be a skybox and the Player and the home base
            }
			if (ImGui::MenuItem("Add Planets")) {  // this will randomly add a set number of planets to the scene
				//ShouldAddPlanet = true;
                
            }
			if (ImGui::MenuItem("Add Asteroid's")) {  // this will randomly add asteroids to the scene
				//ShouldAddAsteroid = true;
               
            }
			if (ImGui::MenuItem("Add random space junk")) { // this will randomly add space junk to the scene
				//ShouldAddSpaceJunk = true;
               
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Add a new mesh")) {

            
            if (ImGui::MenuItem("Add OBJ")) {

                //ShouldAddEditMesh = true;
                //dialogType = false;   // sets is textured or obj file for the opendialog box

            }
            if (ImGui::MenuItem("Cube")) {
                // set ShouldAddCube to true then add cube to the tree
                //ShouldAddCube = true;
                //dialogType = true;   // sets dialogType is textured or obj file for the opendialog box

            }
            if (ImGui::MenuItem("Plane")) {
                // set ShouldAddPlane to true then add plane to the tree
                //ShouldAddPlane = true;
                //dialogType = true;
            }
            if (ImGui::MenuItem("Sphere")) {
                //ShouldAddSphere = true;
               
            }
            if (ImGui::MenuItem("Cylinder")) {}
            
            if (ImGui::MenuItem("Grid")) {}
           
            if (ImGui::MenuItem("Pyramid")) {
                //ShouldAddPyramid = true;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Add a new Light")) {
            if (ImGui::MenuItem("Sun Light")) {
                //ShouldAddSunLight = true;
               // LightSelector = LIGHT_SUN;
            }
            if (ImGui::MenuItem("Point Light")) {
               // ShouldAddPointLight = true;
               // LightSelector = LIGHT_POINT;
            }
            if (ImGui::MenuItem("Spot Light")) {
               // ShouldAddSpotLight = true;
               // LightSelector = LIGHT_SPOT;
            }
            if (ImGui::MenuItem("Area Light")) {
                //ShouldAddAreaLight = true;
                //LightSelector = LIGHT_AREA;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Add a Terrain")) {
            if (ImGui::MenuItem("Terrain")) { // This is the main terrain
                //ShouldAddTerrain = true;
            }
            if (ImGui::MenuItem("Water")) {}
            if (ImGui::MenuItem("Floor")) {  // This is the floor
                //ShouldAddFloor = true;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Add a Sky")) {
            if (ImGui::MenuItem("Sky Box")) { // This is the skybox on the main terrain

            }
            if (ImGui::MenuItem("Hemisphere")) {
            }
            if (ImGui::MenuItem("HDRI Skybox")) {  
                
            }

            ImGui::EndMenu();
        }

        ImGui::EndPopup();
    }


    ImGui::Text("Right-click for popup Menu.");
    ImGui::End();
    ImGui::PopStyleVar();
}
void MainScreen::MainMenuBar(GLFWwindow* window)
{
    // This is my main window menu
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New Level"))
        {

        }
        if (ImGui::MenuItem("Open Level"))
        { 

        }
        
       
        ImGui::Separator();
        if (ImGui::MenuItem(ICON_FA_SAVE" Save Level"))
        {

        }
       
        ImGui::Separator();
        if (ImGui::MenuItem(ICON_FA_SIGN_OUT_ALT" Exit"))
        {
            glfwSetWindowShouldClose(window, true);
        }
        ImGui::EndMenu();

    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Cut"))
        {

        }
        if (ImGui::MenuItem("Copy"))
        {

        }
        if (ImGui::MenuItem("Paste"))
        {

        }
        ImGui::Separator();
        if (ImGui::MenuItem("Wire Frame"))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if (ImGui::MenuItem("Wire Frame off"))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Settings"))
    {
        if (ImGui::MenuItem(ICON_FA_COGS" Open Settings"))
        {
           // show_settings_window = true; // show settings window

        }

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Tools"))
    {
        if (ImGui::MenuItem("Open Tool Box"))
        {

        }

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::MenuItem("Hi"))
        {

        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Run Game"))
    {
        if (ImGui::MenuItem("Run"))
        {


        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("About"))
    {
        if (ImGui::MenuItem("About Screen"))
        {
            //show_about_window = true; // show About Window
        }

        if (ImGui::MenuItem("Help"))
        {

        }
        ImGui::Separator();
        if (ImGui::MenuItem("Window Opacity on"))
        {
            glfwSetWindowOpacity(window, 0.6f);
        }
        if (ImGui::MenuItem("Window Opacity off"))
        {
            glfwSetWindowOpacity(window, 1.0f);
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Visit Web Site"))
        {

        }
        ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
	
}

void MainScreen::WinInit(GLFWwindow* window)
{
	MainScreen::NewImGuiFrame(window);
	ImGui::NewFrame();
	MainScreen::MainMenuBar(window);

    bool p_open = true;
    MainScreen::MainDockSpace(&p_open); // The Doc Space
}


void MainScreen::RenderImGui(GLFWwindow* window)
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_context = glfwGetCurrentContext(); // Get the current window conttext
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_context);
    }
}

void MainScreen::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
}

void MainScreen::BgColor(float BgCol[4])
{
	glClearColor(BgCol[0], BgCol[1], BgCol[2], BgCol[3]); // Set the main window background color
}







