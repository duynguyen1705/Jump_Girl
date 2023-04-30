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
#include <chrono>
#include <vector>
#include <time.h>

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
#define MAX_TILES 18
#define numberOfMap 8
#define BLANKTILE 0
#define CharFrames 5


//file name
const char MenuVolumeOn_File_Name[] = { "Map/Menu_VolumeOn.png" };
const char MenuVolumeOff_File_Name[] = { "Map/Menu_VolumeOff.png" };
const char Victory_File_Name[] = { "Map/Victory.png" };
const char Turtorial_File_Name[] = { "Map/Tutorial.png" };
const char Introduce_File_Name[] = { "Map/Introduce.png" };

const char Level_File_Name[] = { "Map/Level.png" };
const char Map_File_Name1[] = { "Map/TileMap.txt" };
const char Map_File_Name2[] = { "Map/TileMap2.txt" };
const char Map_File_Name3[] = { "Map/TileMap3.txt" };

const char Right_File_Name[] = { "Img/Walk_RIGHT.png" };
const char Left_File_Name[] = { "Img/Walk_LEFT.png" };
const char Jump_Right_File_Name[] = { "Img/RIGHT.png" };
const char Jump_Left_File_Name[] = { "Img/LEFT.png" };
const char Jump_Up_File_Name[] = { "Img/UP.png" };

const char FirstTime_Position[] = { "Map/FirstPos.txt" };
const char Save_Position[] = { "Map/Last.txt" };
const char High_Score_Save[] = { "Map/HighScore.txt" };
const char Time_Save_File[] = { "Map/TimeSave.txt" };
const char Map_Save_File[] = { "Map/MapSave.txt" };

const char InGame_Sound_File[] = { "Sound/MixSong.mp3" };
const char Menu_Sound_File[] = { "Sound/ShadowOfTheSun.mp3" };
const char Win_Sound_File[] = { "Sound/ChampionLeagueSong.mp3" };

const char font[] = { "Font//ShortBaby-Mg2w.ttf" };
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