#ifndef _PLAYER_
#define _PLAYER_

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
	static const int playerStretch = 3; // Растягивание спрайта игрока
public:
	static const int PLAYER_WIDTH = 16 * playerStretch;
	static const int PLAYER_HEIGHT = 16 * playerStretch;

	static const int PLAYER_VEL = 5;
	
	std::array<itemNamespace::ItemTypes, 3> inventory;

	float Health;

	Player();
	void handleEvent(SDL_Event &e);
	void update(const std::vector<Wall>&, std::vector<Item> &);
	void render();
	const SDL_Rect *getCollider();
	bool isCollised();
	void setPosition(int x, int y);
	void clearInventory();

	const int &x = mPosX;
	const int &y = mPosY;

	

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

#endif