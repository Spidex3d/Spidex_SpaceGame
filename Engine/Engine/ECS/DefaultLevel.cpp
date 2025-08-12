#include <imgui\imgui.h>
#include <imgui\ImGuiAF.h>
#include <iostream>
#include "DefaultLevel.h"
#include "../../../Editor/src/GlobalVars.h"

DefaultLevel::DefaultLevel(int idx, const std::string& name, int LevelIdx)
{
	index = idx;             // list index
	objectName = name;       // grid name
	objectIndex = idx;       // grid index
	objectTypeID = LEVEL_SKY_BOX;        // Example type ID for Level = 30

}
DefaultLevel::~DefaultLevel()
{
	// Destructor logic if needed
}
DefaultLevel* DefaultLevel::Instance()
{
	static DefaultLevel* leveleditor;
	return leveleditor;	
}



// This is the default level editor window, it will be used to create and edit levels in the game.
void DefaultLevel::Initialize()
{
}

inline std::vector<DefaultLevel> DefaultLevel::loadLevelTextureFromFolder(const std::string& folderPath)
{
	return std::vector<DefaultLevel>();
}

inline unsigned char* DefaultLevel::extract_face(const unsigned char* src, int srcWidth, int srcHeight, int channels, int faceRow, int faceCol, int faceSize)
{
	return nullptr;
}

void DefaultLevel::LevelEditorWindow()
{
	// Just load a player and grid for now, this will be the default level editor window.
	if (ShowLevelEditor) {
		ImGui::GetStyle().WindowRounding = 12.0f;
		ImGui::Begin("LevelEditor");
		ImGui::Text("Default Level Editor");
		ImGui::Text("This is the default level editor window.");

		if (ImGui::CollapsingHeader(ICON_FA_EDIT" Star Feild Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			// add a skybox to the scene
		}

		if (ImGui::CollapsingHeader(ICON_FA_EDIT" Planet Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			// randomly generate 3 planets in the scene
			// at a later time we need to add collision detection to the planets
		}
		if (ImGui::CollapsingHeader(ICON_FA_EDIT" Asteroid Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			// randomly generate 10 asteroids in the scene
			// at a later time we need to add collision detection to the asteroids
		}
		if (ImGui::CollapsingHeader(ICON_FA_EDIT" Space Junk Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			// randomly generate 20 space junk items in the scene
			// this will be used for collecting items in the game
		}
		if (ImGui::CollapsingHeader(ICON_FA_EDIT" Player Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Player Index: %d", PlayerIdx);
			ImGui::InputText("Player Name", nameBuffer, sizeof(nameBuffer));
			if (ImGui::Button("Add Player")) {
				// Logic to add a player to the scene
				std::cout << "Adding Player: " << nameBuffer << std::endl;
				ShouldAddPlayer = true; // this will add a player to the scene
				
			}
		}

		if (ImGui::Button("Create Default Level")) {
			// Logic to create a default level
			std::cout << "Creating Default Level..." << std::endl;
			ShoulAddStarFeild = true;	// this will add a star field to the scene ! SkyBox
			ShouldAddPlanets = true;	// this will add planets to the scene
			ShouldAddAsteroids = true;  // this will add asteroids to the scene
			ShouldAddSpaceJunk = true;  // this will add space junk to the scene for collecting
			ShouldAddPlayer = true;		// this will add a player to the scene

			// ShouldAddDefaultLevel = true; // This will add a default level to the scene
			ShowLevelEditor = false; // Hide the level editor window after creating the level
		}
		ImGui::End();
	}
}
