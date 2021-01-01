#include "Player.h"
 


Player::Player()
{
	mFrame = 0;
	mPosX = 200;
	mPosY = 200;
	mVelX = 0;
	mVelY = 0;
	Health = 167;
	mStopDestination = UP;
	mDestination = DEFAULT;
	mCurrentClip = nullptr;
	mCollider.w = PLAYER_WIDTH;
	mCollider.h = PLAYER_HEIGHT;
	detectCollision = false;
	for (ItemTypes &i : inventory)
	{
		i = ItemTypes::EMPTY;
	}
}

void Player::eventHandler(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY -= PLAYER_VEL; /*mDestination = UP;*/ break;
		case SDLK_a: mVelX -= PLAYER_VEL; /*mDestination = LEFT;*/ break;
		case SDLK_s: mVelY += PLAYER_VEL; /*mDestination = DOWN;*/ break;
		case SDLK_d: mVelX += PLAYER_VEL; /*mDestination = RIGHT;*/  break;
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY += PLAYER_VEL; /*mStopDestination = UP; mDestination = DEFAULT;*/ break;
		case SDLK_a: mVelX += PLAYER_VEL; /*mStopDestination = LEFT; mDestination = DEFAULT;*/ break;
		case SDLK_s: mVelY -= PLAYER_VEL; /*mStopDestination = DOWN; mDestination = DEFAULT;*/ break;
		case SDLK_d: mVelX -= PLAYER_VEL; /*mStopDestination = RIGHT; mDestination = DEFAULT;*/ break;
		}

	}
}


void Player::move(const std::vector<SDL_Rect> &walls, std::vector<Item> &items)
{
	mPosX += mVelX;
	mCollider.x = mPosX;
	for (const auto &i : walls) 
	{
		if (mPosX < 33 || mPosX + PLAYER_WIDTH > SCREEN_WIDTH - 33 || checkCollision(mCollider, i))
		{
			mPosX -= mVelX;
			mCollider.x = mPosX;
		}
	}


	mPosY += mVelY;
	mCollider.y = mPosY;
	for (const auto &i : walls)
	{
		if (mPosY < 190 - PLAYER_WIDTH || mPosY + PLAYER_HEIGHT  > SCREEN_HEIGHT - 23 || checkCollision(mCollider, i))
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
			for (int k = 0;k<3;k++) 
			{
				if (inventory[k] == ItemTypes::EMPTY)
				{
					inventory[k] = item.type;
					items.erase(items.begin() + index);
					break;
				}
				
			}
			
		}
		index++;
	}
/*
	if (checkCollision(mCollider, keyItem))
	{
		inventory[0] = PlayerItems::KEY;
		keyItem.x = 10000;
	}
	*/
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
		case UP: currentStopDestination = &gAnimationFrame[UP][1]; break;
		case LEFT: currentStopDestination = &gAnimationFrame[LEFT][1]; break;
		case RIGHT: currentStopDestination = &gAnimationFrame[RIGHT][1]; break;
		case DOWN: currentStopDestination = &gAnimationFrame[DOWN][1]; break;
		}

		gPlayerTexture.render(mPosX, mPosY, PLAYER_WIDTH , PLAYER_HEIGHT , currentStopDestination);

	}

	++mFrame;
	if (mFrame / 6 >= 3)
		mFrame = 0;

}

SDL_Rect Player::getCollider()
{
	return mCollider;
}

bool Player::isCollised()
{
	return detectCollision;
}

