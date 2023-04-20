#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Rect camera;
static int map_level;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 16;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff;

const int FRAME_PER_SECOND = 37;

#define TILE_SIZE 50
#define MAX_MAP_X 24
#define MAX_MAP_Y 112
#define MAX_TILES 11
#define numberOfMap 8


//file name
const char MenuVolumeOn_File_Name[] = { "Map/Menu_VolumeOn.png" };
const char MenuVolumeOff_File_Name[] = { "Map/Menu_VolumeOff.png" };
const char Victory_File_Name[] = { "Map/Victory.png" };
const char Turtorial_File_Name[] = { "Map/Tutorial.png" };
const char Map_File_Name[] = { "Map/TileMap.txt" };
const char Right_File_Name[] = { "Img/Walk_RIGHT.png" };
const char Left_File_Name[] = { "Img/Walk_LEFT.png" };
const char Jump_Right_File_Name[] = { "Img/RIGHT.png" };
const char Jump_Left_File_Name[] = { "Img/LEFT.png" };
const char Jump_Up_File_Name[] = { "Img/UP.png" };
const char FirstTime_Position[] = { "Map/pos.txt" };
const char Save_Position[] = { "Map/Pos_.txt" };

typedef struct
{
	int LEFT_;
	int RIGHT_;
	int UP_;
	int d_;
	int a_;
} Input;

typedef struct
{
	int tile[MAX_MAP_Y][MAX_MAP_X];
	string file_name_;
} Map;

typedef struct Block
{
	int x_min;
	int x_max;
	int y_min;
	int y_max;
	Block(int x_min_, int x_max_, int y_min_, int y_max_)
	{
		x_min = x_min_;
		x_max = x_max_;
		y_min = y_min_;
		y_max = y_max_;
	}
};
#endif