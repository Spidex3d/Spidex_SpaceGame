#pragma once
#include "BaseModel.h"
#include<vector>

// This will set up the start level for the game, It will open a window with lots of settings and options to set
// Then generate a default level with a skybox, player, home base in space not on a planet, asteroids, and random space junk.
// Start point for the game development, this will be the first level that is generated when the game starts.
// The engine will chek if this exsist if so not it will open a window with the settings and options to set one up.
// I woulud like if this was randomly generated with a skybox, player, home base in space not on a planet, asteroids, and random space junk.
class DefaultLevel : public BaseModel
{
public:
	DefaultLevel() = default; // Default constructor
	~DefaultLevel();

	static DefaultLevel* Instance();

	void Initialize();
	DefaultLevel(int idx, const std::string& name, int LevelIdx);

	inline std::vector<DefaultLevel> loadLevelTextureFromFolder(const std::string& folderPath);
	inline unsigned char* extract_face(const unsigned char* src, int srcWidth, int srcHeight, int channels,
		int faceRow, int faceCol, int faceSize = 512);

	void LevelEditorWindow();

private:
	
	
};

