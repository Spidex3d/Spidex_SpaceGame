#pragma once
#include <imgui\imgui.h>

extern const int SCR_WIDTH;
extern const int SCR_HEIGHT;
extern const char* SCR_TITLE;

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

extern const int MAIN_GRID;
