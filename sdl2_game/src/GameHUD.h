#pragma once
#include "init.h"
#include "GameTexture.h"
#include "Player.h"
#include "textures.h"

class GameHUD
{
public:
	GameHUD(Player* PlyerPtr);
	void update();
	void render();

private:
	Player *player{ nullptr };
	SDL_Rect InventorySlot;
	SDL_Rect HealthBar;
	std::stringstream healthBarText;
	GameTexture HealthBarTexture;
	GameTexture LevelNameTexture;
	GameTexture LevelNumberTexture;
	SDL_Color textColor = { 0, 0, 0 };
};

