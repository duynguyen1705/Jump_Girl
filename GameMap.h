#ifndef MAP_H_
#define MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"


class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(string name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen, int level);
	Map getMap() const { return game_map_; }
	Map setMap(Map& map_data) { game_map_ = map_data; }
private:
	Map game_map_;
	TileMap tile_map[MAX_TILES];
};

#endif
