#pragma once
#include "EngineCore.h"
#include "textures.h"

class GameMapLoader
{
public:
	GameMapLoader();
	void loadMap(unsigned int levelNum = 0);
	void render();
	
	std::vector<Item> items;
	std::vector<SDL_Rect> walls;
private:
	std::ifstream mapfile;
	std::ifstream fileIn;
	nlohmann::json mMapList{};
	nlohmann::json mMap{};
};

