#include "GameHUD.h"

GameHUD::GameHUD(Player *ptrPlyer)
{
	player = ptrPlyer;
	InventorySlot = { 0, 600, 60, 60 };
	HealthBar = { 500, 625, 250, 30 };

	//Пробросить доступ к строкам название уровня и номеро уровня, когда будет готов загрузчить карт
	LevelNameTexture.loadFromRenderedText(levelNumAndName[0], textColor, gFont);
	LevelNumberTexture.loadFromRenderedText(levelNumAndName[1], textColor, gFont12);
}

void GameHUD::update()
{
	healthBarText.str("");
	healthBarText << "Health " << player->Health << "%";
	if (!HealthBarTexture.loadFromRenderedText(healthBarText.str().c_str(), textColor))
	{
		printf("Unable to render HEALTH TEXT!\n");
	}
	LevelNameTexture.loadFromRenderedText(levelNumAndName[0], textColor, gFont);
	LevelNumberTexture.loadFromRenderedText(levelNumAndName[1], textColor, gFont12);
}

void GameHUD::render()
{
	InventorySlot.x = 960;
	for (int iii = 0; iii < 3; iii++)
	{

		InventorySlot.x += 70;
		SDL_SetRenderDrawColor(gWindow.mRenderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderFillRect(gWindow.mRenderer, &InventorySlot);

		SDL_Rect innerRect = { InventorySlot.x + 2, InventorySlot.y + 2, 56, 56 };
		SDL_Rect *currentItemClip = nullptr;

		if (player->inventory[iii] != itemNamespace::EMPTY)
		{
			SDL_SetRenderDrawColor(gWindow.mRenderer, 0x63, 0x63, 0x63, 0xff);
			SDL_RenderFillRect(gWindow.mRenderer, &innerRect);
			switch(player->inventory[iii])
			{
			case itemNamespace::KEY:
			case itemNamespace::SWORD:
				currentItemClip = &gItemsTextureClips[player->inventory[iii]];
			}
			
			gItemsTexture.render(innerRect.x, innerRect.y, innerRect.w, innerRect.h, currentItemClip);
		}
		else
		{

			SDL_SetRenderDrawColor(gWindow.mRenderer, 0x63, 0x63, 0x63, 0xff);
			SDL_RenderFillRect(gWindow.mRenderer, &innerRect);
		}
	}

	//Отрисовка полоски жизни игрока
	HealthBarTexture.render(HealthBar.x + 47, HealthBar.y - HealthBarTexture.getHeight());
	
	SDL_SetRenderDrawColor(gWindow.mRenderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(gWindow.mRenderer, &HealthBar);
	
	SDL_Rect innerHealthBarBg = { 
		HealthBar.x + 3,
		HealthBar.y + 3,
		HealthBar.w - 6,
		HealthBar.h - 6 };
	SDL_SetRenderDrawColor(gWindow.mRenderer, 0xC0, 0xC0, 0xC0, 0xff);
	SDL_RenderFillRect(gWindow.mRenderer, &innerHealthBarBg);

	SDL_Rect innerHealthBarUp = { 
		HealthBar.x + 3,
		HealthBar.y + 3,
		HealthBar.w - (244 - static_cast<int>(player->Health * 2.44)) - 6, 
		HealthBar.h - 6 };
	SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(gWindow.mRenderer, &innerHealthBarUp);


	LevelNameTexture.render(45, 610);
	LevelNumberTexture.render(45, 640);
}