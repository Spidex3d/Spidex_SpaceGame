#include "GlobalVars.h"

std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models
int currentIndex = -1;
char nameBuffer[128] = ""; // buffer for object names

GLuint main_scene_texture_id = 0; // Main scene texture ID

// Grid
bool gridNogrid = false; // toggle for grid visibility
float grid_square = 2;
int grid_size = 40;

// Level settings
const int LEVEL_SKY_BOX = 30;
int LevelIdx = 0;
bool ShoulAddStarFeild = true;
bool ShouldAddPlanets = true;
bool ShouldAddAsteroids = true;
bool ShouldAddSpaceJunk = true;
bool ShouldAddPlayer = false; // Toggle for adding a player object
bool ShowLevelEditor = false; // Toggle for showing the level editor window;

// Player
int PlayerIdx = 0; //  player object index


// Settings
float BgCol[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Background color for the main window


// Screen settings
const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;
const char* SCR_TITLE = "Spidex Space Game Editor";
bool GameFullScreen = false; // Fullscreen mode toggle;
const char* SCR_TITLE_GAME = "Spidex Space Game";

// object indexes
int Gridobjidx = 0; // Index for the grid object
// Object type IDs
const int MAIN_GRID = 0;
const int OBJ_CUBE = 1;
const int OBJ_SPHERE = 1;

// Player object type IDs
extern const int MAIN_PLAYER = 0;

// Enimy object type IDs
extern const int MAIN_ENIMY = 0;