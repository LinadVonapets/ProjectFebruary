#pragma once
#include "textures.h"


//Направление игрока
enum PlayerDestinaion
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
	DEFAULT
};

class Player
{
	static const int playerStretch = 3;
public:
	static const int PLAYER_WIDTH = 16 * playerStretch;
	static const int PLAYER_HEIGHT = 16 * playerStretch;

	static const int PLAYER_VEL = 5;
	
	item::ItemTypes inventory[3];

	short Health;
	Player();
	void eventHandler(SDL_Event &e);
	void move(const std::vector<SDL_Rect>&, std::vector<Item> &);
	void render();
	const SDL_Rect *getCollider();
	bool isCollised();
	

private:
	int mPosX, mPosY;
	int mVelX, mVelY;
	int mFrame;
	PlayerDestinaion mStopDestination;
	PlayerDestinaion mDestination;
	SDL_Rect *mCurrentClip;
	SDL_Rect mCollider;
	bool detectCollision;
	short destFrames = sizeof(gAnimationFrame[0]) / sizeof(gAnimationFrame[0][0]);
	
};

