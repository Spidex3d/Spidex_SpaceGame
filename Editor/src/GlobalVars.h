#pragma once
#include <glad/glad.h>
#include <imgui\imgui.h>
#include <vector>
#include <memory>
#include "../../Engine/Engine/ECS/BaseModel.h"

#define M_PI 3.14159265358979323846

extern std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models
extern int currentIndex;
extern char nameBuffer[128];

extern GLuint main_scene_texture_id; // Main scene texture ID

// Grid
extern bool gridNogrid; // toggle for grid visibility
extern float grid_square;
extern int grid_size;

// Level settings
extern const int LEVEL_SKY_BOX;
extern int LevelIdx;
extern bool ShouldAddPlayer;
extern bool ShowLevelEditor;
// Player
extern int PlayerIdx; //  player object index

// Settings
extern float BgCol[4]; // Background color for the main window


extern const int SCR_WIDTH;
extern const int SCR_HEIGHT;
extern const char* SCR_TITLE;
extern bool GameFullScreen;
extern const char* SCR_TITLE_GAME;

extern int Gridobjidx;

// Object type IDs
extern const int MAIN_GRID;
extern const int OBJ_CUBE;
extern const int OBJ_SPHERE;

// Player object type IDs
extern const int MAIN_PLAYER;

// Enimy object type IDs
extern const int MAIN_ENIMY;



// Font indices for different font sizes
enum FontIndex : int {
	REG_FONT_INDEX = 0,
	SMALL_FONT_INDEX,
	TINY_FONT_INDEX,
};

//const float FONT_SIZE = 28.0f; // comic
const float FONT_SIZE = 20.0f; // comic
const float SMALL_FONT_SIZE = 13.0f;
const float TINY_FONT_SIZE = 10.0f;

constexpr const char* FONT_PATH_MAIN = "Fonts/comic.ttf";

constexpr const char* ROBOTO_REG_PATH = "Fonts/Roboto-Regular.ttf";
constexpr const char* FA_REG_PATH = "Fonts/FA-Regular-400.otf";
constexpr const char* FA_SOLID_PATH = "Fonts/FA-Solid-900.otf";

// Colors
const ImVec4 COLOR_LIGHTBLUE(0.43f, 0.7f, 0.89f, 1.0f);
const ImVec4 COLOR_LIGHTGREEN(0.0f, 0.9f, 0.0f, 1.0f);
const ImVec4 COLOR_NONE(0.0f, 0.0f, 0.0f, 0.0f);

