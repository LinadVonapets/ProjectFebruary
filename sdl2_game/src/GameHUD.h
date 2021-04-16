#ifndef _GAME_HUD_
#define _GAME_HUD_

#include "EngineCore.h"
#include "GameTexture.h"
#include "Player.h"
#include "textures.h"

class GameHUD
{
public:
	GameHUD(Player* ptrPlyer);
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

#endif 
