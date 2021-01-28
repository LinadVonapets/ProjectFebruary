#include "Player.h"
#include "GameTexture.h"
#include "init.h"
#include "GameHUD.h"

GameTexture gItemsTexture;
GameTexture gPlayerTexture;
GameTexture gBackgroundTexture;
GameTexture gHealthBarText;
SDL_Rect gAnimationFrame[4][3];
SDL_Rect gWallClip;
SDL_Rect gBricksClip[2];
SDL_Rect gItemsTextureClips[item::TOTAL];

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
		gWallClip = { 32, 32, 161, 161 }; //������������ �����
		gBricksClip[0] = { 32, 0, 48, 33 }; //�������������� ������
		gBricksClip[1] = { 0, 0, 33, 48 }; //������������ ������
	}

	if (!gItemsTexture.loadFromFile("images/items.png"))
	{
		printf("Failed to load items texture!\n");
		success = false;
	}
	else
	{
		gItemsTextureClips[item::KEY] = { 321, 1129, 144, 150 }; // �������� �����
		gItemsTextureClips[item::SWORD] = { 1119, 639, 160, 160 };
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



	SDL_Rect wall = { 30, 400, 400, 40 };
	SDL_Rect wall2 = { 430, 150, 40, 100 };
	SDL_Rect wall3 = { 430, 340, 40, 100 };

	std::vector<SDL_Rect> Walls = { wall, wall2, wall3};


	Item keyItem = { { 500, 500, 40, 40 }, item::KEY };
	Item keyItem2 = { { 500, 600, 40, 40 }, item::SWORD };

	std::vector<Item> Items = { keyItem, keyItem2 };



	GameHUD HUD(&player);

	while (!quit)
	{
		for (; SDL_PollEvent(&e) != 0;)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				quit = true;
			}
			player.eventHandler(e);
			gWindow.handleEvent(e);
		}

		if (!gWindow.isMinimized())
		{
			player.move(Walls, Items);

			SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0xff, 0xff, 0xff);
			SDL_RenderClear(gWindow.mRenderer);

			gBackgroundTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			for(int i=0, dist=140; i < 3; i++)
				gBackgroundTexture.render(31 + dist * i, 400, 160, 160, &gWallClip);
			for (int i = 0, dist = 47; i < 10; i++)
			{
				if (i > 4 && i < 7)
					continue;
				gBackgroundTexture.render(436, 32 + dist * i, 33, 48, &gBricksClip[1]);
			}

			player.render();
			SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
			SDL_RenderDrawRect(gWindow.mRenderer, player.getCollider());


			for (const auto &i : Walls)
			{
				SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
				SDL_RenderDrawRect(gWindow.mRenderer, &i);
			}
			
			for (const auto &i : Items)
			{
				SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0xff, 0x00, 0xff);
				SDL_RenderDrawRect(gWindow.mRenderer, &i.collider);
				
				switch (i.type)
				{
				case item::KEY:
				case item::SWORD:
					gItemsTexture.render
					(	i.collider.x,
						i.collider.y,
						i.collider.w, 
						i.collider.h,
						&gItemsTextureClips[i.type]
					);
				}
				
			}

			HUD.update();
			HUD.render();
			
			SDL_RenderPresent(gWindow.mRenderer);
		}
		
	}
	close();
	return 0;
}