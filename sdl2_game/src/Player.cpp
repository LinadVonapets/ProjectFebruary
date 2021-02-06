#include "Player.h"
 


Player::Player()
{
	mFrame = 0;
	mPosX = (SCREEN_WIDTH / 2) - PLAYER_WIDTH;
	mPosY = (SCREEN_HEIGHT / 2) - PLAYER_HEIGHT;
	mVelX = 0;
	mVelY = 0;
	Health = 100;
	mStopDestination = UP;
	mDestination = DEFAULT;
	mCurrentClip = nullptr;
	mCollider.w = PLAYER_WIDTH;
	mCollider.h = PLAYER_HEIGHT;
	detectCollision = false;
	for (itemNamespace::ItemTypes &i : inventory)
	{
		i = itemNamespace::EMPTY;
	}
}

void Player::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY -= PLAYER_VEL; break;
		case SDLK_a: mVelX -= PLAYER_VEL; break;
		case SDLK_s: mVelY += PLAYER_VEL; break;
		case SDLK_d: mVelX += PLAYER_VEL; break;
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY += PLAYER_VEL; break;
		case SDLK_a: mVelX += PLAYER_VEL; break;
		case SDLK_s: mVelY -= PLAYER_VEL; break;
		case SDLK_d: mVelX -= PLAYER_VEL; break;
		}

	}
}


void Player::update(const std::vector<Wall> &walls, std::vector<Item> &items)
{

	mPosX += mVelX;
	mCollider.x = mPosX;

	mPosY += mVelY;
	mCollider.y = mPosY;

	if (mPosX < 33 || mPosX + PLAYER_WIDTH > SCREEN_WIDTH - 33)
	{
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}
	if (mPosY < 190 - PLAYER_WIDTH || mPosY + PLAYER_HEIGHT  > SCREEN_HEIGHT - 23)
	{
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}

	for (const auto &i : walls) 
	{
		if (checkCollision(mCollider, i.collider))
		{
			mPosX -= mVelX;
			mCollider.x = mPosX;
		}
	}

	for (const auto &i : walls)
	{
		if (checkCollision(mCollider, i.collider))
		{
			mPosY -= mVelY;
			mCollider.y = mPosY;
		}
	}

	int index=0;
	for (const auto &item : items)
	{
		
		if (checkCollision(mCollider, item.collider))
		{
			for (int k = 0; k < 3; k++)
			{
				if (inventory[k] == itemNamespace::EMPTY)
				{
					inventory[k] = item.type;
					items.erase(items.begin() + index);
					break;
				}
			}
		}
		index++;
	}

	if (Health > 100)
		Health = 100;
	if (Health < 0)
		Health = 0;

	if (plyrShwPos)
		std::cout << "X: " << mPosX << " Y: " << mPosY << "\n";
}

void Player::render()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_S])
	{
		mDestination = DEFAULT;
	}
	else if (currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D])
	{
		mDestination = DEFAULT;
	}
	else if (currentKeyStates[SDL_SCANCODE_W])
	{
		mDestination = UP;
		mStopDestination = UP;
	}
	else if (currentKeyStates[SDL_SCANCODE_S])
	{
		mDestination = DOWN;
		mStopDestination = DOWN;
	}
	else if (currentKeyStates[SDL_SCANCODE_A])
	{
		mDestination = LEFT;
		mStopDestination = LEFT;
	}
	else if (currentKeyStates[SDL_SCANCODE_D])
	{
		mDestination = RIGHT;
		mStopDestination = RIGHT;
	}
	else
	{
		mDestination = DEFAULT;
	}


	switch (mDestination)
	{
	case DOWN:
		mCurrentClip = &gAnimationFrame[DOWN][mFrame / 6];
		gPlayerTexture.render(mPosX, mPosY, PLAYER_WIDTH, PLAYER_HEIGHT , mCurrentClip);
		break;

	case UP:
		mCurrentClip = &gAnimationFrame[UP][mFrame / 6];
		gPlayerTexture.render(mPosX, mPosY, PLAYER_WIDTH , PLAYER_HEIGHT , mCurrentClip);
		break;

	case LEFT:
		mCurrentClip = &gAnimationFrame[LEFT][mFrame / 6];
		gPlayerTexture.render(mPosX, mPosY, PLAYER_WIDTH , PLAYER_HEIGHT , mCurrentClip);
		break;

	case RIGHT:
		mCurrentClip = &gAnimationFrame[RIGHT][mFrame / 6];
		gPlayerTexture.render(mPosX, mPosY, PLAYER_WIDTH , PLAYER_HEIGHT , mCurrentClip);
		break;

	default:
		SDL_Rect *currentStopDestination = nullptr;
		switch (mStopDestination)
		{
		case UP: currentStopDestination = &gAnimationFrame[UP][destFrames/2]; break;
		case LEFT: currentStopDestination = &gAnimationFrame[LEFT][destFrames/2]; break;
		case RIGHT: currentStopDestination = &gAnimationFrame[RIGHT][destFrames / 2]; break;
		case DOWN: currentStopDestination = &gAnimationFrame[DOWN][destFrames / 2]; break;
		}

		gPlayerTexture.render(mPosX, mPosY, PLAYER_WIDTH , PLAYER_HEIGHT , currentStopDestination);

	}

	++mFrame;
	if (mFrame / 6 >= 3)
		mFrame = 0;

	if (debug_mode)
	{
		SDL_SetRenderDrawColor(gWindow.mRenderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderDrawRect(gWindow.mRenderer, &mCollider);
	}
}

const SDL_Rect *Player::getCollider()
{
	return &mCollider;
}

bool Player::isCollised()
{
	return detectCollision;
}

void Player::clearInventory()
{
	for (auto& slot : inventory)
		slot = itemNamespace::EMPTY;
}

void Player::setPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;
}

