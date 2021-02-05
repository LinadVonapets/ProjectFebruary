#pragma once
#include "EngineCore.h"
#include "textures.h"
#include "Player.h"

class GameMapLoader
{
public:
	GameMapLoader(Player *ptrPlyer);
	void loadMap(unsigned int levelNum = 0);
	void render();
	void update();
	
	std::vector<Item> items;
	std::vector<SDL_Rect> walls;
private:
	std::ifstream mapfile;
	std::ifstream fileIn;
	nlohmann::json mMapList{};
	nlohmann::json mMap{};
	Player* player{ nullptr };
	void clearAllEntity();
};

