#include <imgui\imgui.h>
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
		ImGui::Begin("LevelEditor");
		ImGui::Text("Default Level Editor");
		ImGui::Text("This is the default level editor window.");

		if (ImGui::Button("Create Default Level")) {
			// Logic to create a default level
			std::cout << "Creating Default Level..." << std::endl;
			// ShouldAddDefaultLevel = true; // This will add a default level to the scene
			ShowLevelEditor = false; // Hide the level editor window after creating the level
		}
		ImGui::End();
	}
}
