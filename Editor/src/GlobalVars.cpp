#include "GlobalVars.h"

std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models
int currentIndex = -1;
char nameBuffer[128] = ""; // buffer for object names

GLuint main_scene_texture_id = 0; // Main scene texture ID

// Grid
bool gridNogrid = false; // toggle for grid visibility
float grid_square = 2;
int grid_size = 40;




const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;
const char* SCR_TITLE = "Spidex Space Game Editor";
const char* SCR_TITLE_GAME = "Spidex Space Game";

// object indexes
int Gridobjidx = 0; // Index for the grid object
// Object type IDs
const int MAIN_GRID = 0;

// Player object type IDs
extern const int MAIN_PLAYER = 0;

// Enimy object type IDs
extern const int MAIN_ENIMY = 0;