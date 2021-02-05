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
		SDL_Rect wall_buff;
		if (mMap["walls"].contains("default"))
		{
			for (const auto& i : mMap["walls"]["default"])
			{
				wall_buff = { i[0], i[1], i[2], i[3] };
				walls.push_back(wall_buff);
			}
		}
	}
}

void GameMapLoader::render()
{
	if (debug_mode)
	{
		for (const auto& i : walls)
		{
			SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
			SDL_RenderDrawRect(gWindow.mRenderer, &i);
		}
	}
	for (const auto& i : items)
	{
		if (debug_mode)
		{
			SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0xff, 0x00, 0xff);
			SDL_RenderDrawRect(gWindow.mRenderer, &i.collider);
		}
		switch (i.type)
		{
		case itemNamespace::KEY:
		case itemNamespace::SWORD:
			gItemsTexture.render
			(i.collider.x,
				i.collider.y,
				i.collider.w,
				i.collider.h,
				&gItemsTextureClips[i.type]
			);
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
