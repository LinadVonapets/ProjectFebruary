#include "Player.h"
#include "GameTexture.h"
#include "EngineCore.h"
#include "GameHUD.h"
#include "GameMapLoader.h"

GameTexture gItemsTexture;
GameTexture gPlayerTexture;
GameTexture gBackgroundTexture;
SDL_Rect gAnimationFrame[4][3];
SDL_Rect gItemsTextureClips[itemNamespace::TOTAL];

//Тестовые текстуры
SDL_Rect gWallClip;
SDL_Rect gBricksClip[2];
SDL_Color textColor = { 0, 0, 0 };

bool loadMedia()
{
	bool success = true;

	gFont = TTF_OpenFont("fonts/fixedsys.ttf", 28);
	if (gFont == nullptr)
	{
		printf("Failed to load FIXEDSYS font 28!\n");
		success = false;
	}

	gFont12 = TTF_OpenFont("fonts/fixedsys.ttf", 20);
	if (gFont == nullptr)
	{
		printf("Failed to load FIXEDSYS font 12!\n");
		success = false;
	}

	if (!gBackgroundTexture.loadFromFile("images/levelBackgrounds/level1.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	else
	{
		gWallClip = { 32, 32, 161, 161 }; //Вертикальная стена
		gBricksClip[0] = { 32, 0, 48, 33 }; //Горизонтальный кирпич
		gBricksClip[1] = { 0, 0, 33, 48 }; //Вертикальный кирпич
	}

	if (!gItemsTexture.loadFromFile("images/items.png"))
	{
		printf("Failed to load items texture!\n");
		success = false;
	}
	else
	{
		gItemsTextureClips[itemNamespace::KEY] = { 321, 1129, 144, 150 }; // Текстура ключа
		gItemsTextureClips[itemNamespace::SWORD] = { 1119, 639, 160, 160 };
	}


	if (!gPlayerTexture.loadFromFile("images/player/01-colorful.png"))
	{
		printf("Failed to load player sheet texture!\n");
		success = false;
	}
	else
	{
		int y_src = 0;
		for (int i = 0; i < DEFAULT; ++i)
		{
			gAnimationFrame[i][0] = { 0, y_src, 16, 16 };
			gAnimationFrame[i][1] = { 16, y_src, 16, 16 };
			gAnimationFrame[i][2] = { 32, y_src, 16, 16 };

			y_src += 16;
		}
		
	}
	return success;
}

bool playrShwPos = false;

int main(int argc, char *argv[])
{
	if (!LMAI())
	{
		close();
		return 0;
	}


	bool fullscreen = false;
	bool quit = false;
	
	SDL_Event e;

	Player player;
	GameMapLoader mapLoader(&player);
	GameHUD HUD(&player);

	short cheatCode = 0;

	while (!quit)
	{
		for (; SDL_PollEvent(&e) != 0;)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				quit = true;
			}

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_h:
					cheatCode += 3;
					break;
				case SDLK_i:
					cheatCode += 5;
					break;
				case SDLK_t:
					cheatCode -= 7;
					break;
				default:
					cheatCode = 0;
				}
			}
			if (cheatCode == 1)
			{
				if (debug_mode)
				{
					debug_mode = false;
					cheatCode = 0;
				}
				else
				{
					debug_mode = true;
					cheatCode = 0;
				}
			}
			if (!(cheatCode == 3 || cheatCode == 8) || cheatCode < 0)
				cheatCode = 0;
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c)
				player.clearInventory();

			player.handleEvent(e);
			gWindow.handleEvent(e);
		}

		if (!gWindow.isMinimized())
		{
			mapLoader.update();
			player.update(mapLoader.walls, mapLoader.items);
			HUD.update();

			SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0xff, 0xff, 0xff);
			SDL_RenderClear(gWindow.mRenderer);

			gBackgroundTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			


			for (int i = 0, dist = 140; i < 2; i++)
			{
				gBackgroundTexture.render(31 + dist * i, 350, 160, 160, &gWallClip);
				gBackgroundTexture.render(950 + dist * i, 350, 160, 160, &gWallClip);
			}
			for (int i = 0, dist = 47; i < 10; i++)
			{
				if (i > 4 && i < 7)
					continue;
				gBackgroundTexture.render(447, 32 + dist * i, 33, 48, &gBricksClip[1]);
				gBackgroundTexture.render(800, 32 + dist * i, 33, 48, &gBricksClip[1]);
			}

			

			mapLoader.render();
			player.render();
			HUD.render();
			
			SDL_RenderPresent(gWindow.mRenderer);
		}
		else
		{
			SDL_Delay(100);
		}
		
	}
	close();
	return 0;
}