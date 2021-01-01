#include "GameWindow.h"

GameWindow::GameWindow()
{
	mWindow = nullptr;
	mRenderer = nullptr;

	mWidth = 0;
	mHeight = 0;

	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullscreen = false;
	mMinimized = false;
	mShown = false;
}

bool GameWindow::init()
{
	mWindow = SDL_CreateWindow("Project February", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != nullptr)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == nullptr)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = nullptr;
		}
		else;
		{
			SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
			mWindowID = SDL_GetWindowID(mWindow);
			mShown = true;
		}
	}
	else
	{
		printf("Window could not to be created! SDL_Error: %s\n", SDL_GetError());
	}

	return mWindow != nullptr && mRenderer != nullptr;
}

void GameWindow::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
	{
		switch (e.window.event)
		{
			//Эти параметры действительны, когда окон несколько
		case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;
			// ------------------------------------------------
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(mRenderer);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(mRenderer);
			break;
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(mWindow);
			break;
		}
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11)
	{
		if (!mFullscreen)
		{
			SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
			mFullscreen = true;
			mMinimized = false;
		}
		else
		{
			SDL_SetWindowFullscreen(mWindow, 0);
			mFullscreen = false;
		}
	}
}

void GameWindow::focus()
{
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}
	SDL_RaiseWindow(mWindow);
}

void GameWindow::free()
{
	if (mWindow != nullptr)
	{
		if (mRenderer != nullptr)
		{
			SDL_DestroyRenderer(mRenderer);
			mRenderer = nullptr;
		}
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
	}
	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}



