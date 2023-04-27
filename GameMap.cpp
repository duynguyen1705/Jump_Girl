#include "GameMap.h"

void GameMap::LoadMap(string name)
{
	ifstream file(name);
	while (!file.eof())
	{
		for (int i = 0; i < MAX_MAP_Y; i++)
		{
			for (int j = 0; j < MAX_MAP_X; j++)
			{
				file >> game_map_.tile[i][j];
			}
		}
	}
	game_map_.file_name_ = name;
	file.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILES; i++)
	{
		sprintf_s(file_img, "Map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);
		tile_map[i].LoadImg(file_img, screen);
	}

}

void GameMap::DrawMap(SDL_Renderer* screen, int level)
{
	int map_x = 0;
	int map_y = 0;
	int numberTilesHeight = SCREEN_HEIGHT / TILE_SIZE;

	for (int i = level * numberTilesHeight; i < (level * numberTilesHeight) + numberTilesHeight; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			int val = game_map_.tile[i][j];
			if (val > 0)
			{
				tile_map[val].SetRect(map_x, map_y);
				tile_map[val].Render(screen, NULL);
			}
			map_x += TILE_SIZE;
		}
		map_y += TILE_SIZE;
		map_x = 0;
	}
}

