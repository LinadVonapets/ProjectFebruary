#include "GameMapLoader.h"


GameMapLoader::GameMapLoader(Player *ptrPlyer) : fileIn("maps/map_list.json")
{
	player = ptrPlyer;
	mMapList = nlohmann::json::parse(fileIn);
	this->loadMap(1);
}

void GameMapLoader::loadMap(unsigned int levelNum)
{
	if (levelNum > 0 && levelNum <= mMapList["maps"].size())
	{
		this->clearAllEntity();
		mapfile.close();
		mapfile.open(mMapList["maps"][levelNum - 1].get<std::string>());
		mMap = nlohmann::json::parse(mapfile);
	}
	else
		mMap = mMapList["empty_level"];

	if (!mMap["player"].empty())
		player->setPosition(mMap["player"]["position"][0].get<int>(), mMap["player"]["position"][1].get<int>());
	else
		player->setPosition((SCREEN_WIDTH / 2) - player->PLAYER_WIDTH, (SCREEN_HEIGHT / 2) - player->PLAYER_HEIGHT);
	
	if (!mMap["level"].empty())
	{
		levelNumAndName[0] = mMap["level"]["name"].get<std::string>();
		levelNumAndName[1] = ("Level " + std::to_string(mMap["level"]["number"].get<int>()));
	}
	else
	{
		levelNumAndName[0] = "\"Level Name\"";
		levelNumAndName[1] = "Level 0" ;
	}
	
	if (!mMap["items"].empty())
	{
		Item item_buff;

		if (mMap["items"].contains("sword"))
		{
			item_buff.type = itemNamespace::SWORD;
			for (const auto& i : mMap["items"]["sword"])
			{
				item_buff.collider = { i[0], i[1], i[2], i[3] };
				items.push_back(item_buff);
			}
			item_buff = {};
		}
		
		if (mMap["items"].contains("keys"))
		{
			item_buff.type = itemNamespace::KEY;
			for (const auto& i : mMap["items"]["keys"])
			{
				item_buff.collider = { i[0], i[1], i[2], i[3] };
				items.push_back(item_buff);
			}
			item_buff = {};
		}

	}
	
	if (!mMap["walls"].empty())
	{
		Wall wall_buff;

		if (mMap["walls"].contains("wood"))
		{
			wall_buff.type = wallNamespace::WOOD_WALL;
			for (const auto& i : mMap["walls"]["wood"])
			{
				wall_buff.collider = { i["collider"][0], i["collider"][1], i["collider"][2], i["collider"][3] };

				if (!i["rect"].empty())
					wall_buff.rect = { i["rect"][0], i["rect"][1], i["rect"][2], i["rect"][3] };
				else
					wall_buff.rect = {};
				
				walls.push_back(wall_buff);
			}
			wall_buff = {};
		}

		if (mMap["walls"].contains("brick"))
		{
			wall_buff.type = wallNamespace::BRICK_VERTICAL;
			for (const auto& i : mMap["walls"]["brick"])
			{
				wall_buff.collider = { i["collider"][0], i["collider"][1], i["collider"][2], i["collider"][3] };

				if (!i["rect"].empty())
					wall_buff.rect = { i["rect"][0], i["rect"][1], i["rect"][2], i["rect"][3] };
				else
					wall_buff.rect = {};

				walls.push_back(wall_buff);
			}
			wall_buff = {};
		}
	}
}

void GameMapLoader::render()
{

	gBackgroundTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Отрисовка сущностей на карте
	
	for (const auto& wall_i : walls)
	{
	
		if (wall_i.type == wallNamespace::WOOD_WALL)
		{
			if (!(wall_i.rect.w == 0 && wall_i.rect.h == 0))
				for (int i = 0, dist = 140; i < 2; i++)
				{
					gBackgroundTexture.render(
						wall_i.rect.x + dist * i, wall_i.rect.y,
						wall_i.rect.w, wall_i.rect.h,
						&gWallsTextureClips[wall_i.type]);
				}
			if (!(wall_i.collider.w == 0 && wall_i.collider.h == 0) && debug_mode)
			{
				SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
				SDL_RenderDrawRect(gWindow.mRenderer, &wall_i.collider);
			}
		}

		if (wall_i.type == wallNamespace::BRICK_VERTICAL)
		{
			if (!(wall_i.rect.w == 0 && wall_i.rect.h == 0))
				for (int i = 0, dist = 47; i < 10; i++)
				{
					if (i > 4 && i < 7)
						continue;
					gBackgroundTexture.render(
						wall_i.rect.x, wall_i.rect.y + dist * i,
						wall_i.rect.w, wall_i.rect.h,
						&gWallsTextureClips[wall_i.type]);
				}
			if (!(wall_i.collider.w == 0 && wall_i.collider.h == 0) && debug_mode)
			{
				SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
				SDL_RenderDrawRect(gWindow.mRenderer, &wall_i.collider);
			}
		}

	}
	
	for (const auto &item_i : items)
	{
		if (debug_mode)
		{
			SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0xff, 0x00, 0xff);
			SDL_RenderDrawRect(gWindow.mRenderer, &item_i.collider);
		}
		switch (item_i.type)
		{
		case itemNamespace::KEY:
		case itemNamespace::SWORD:
			gItemsTexture.render
			(item_i.collider.x,
				item_i.collider.y,
				item_i.collider.w,
				item_i.collider.h,
				&gItemsTextureClips[item_i.type]
			);
			break;
		}
	}
}

void GameMapLoader::update()
{
	if (player->x > 600 && player->x < 630 && player->y == 145)
		for (auto& item : player->inventory)
			if (item == itemNamespace::KEY)
			{
				item = itemNamespace::EMPTY;
				this->loadMap(2);
			}
}

void GameMapLoader::clearAllEntity()
{
	items.clear();
	walls.clear();
}
