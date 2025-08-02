#include "GlobalVars.h"

std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models
int currentIndex = -1;


const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;
const char* SCR_TITLE = "Spidex Space Game Editor";
const char* SCR_TITLE_GAME = "Spidex Space Game";

// Object type IDs
const int MAIN_GRID = 0;

// Player object type IDs
extern const int MAIN_PLAYER = 0;

// Enimy object type IDs
extern const int MAIN_ENIMY = 0;