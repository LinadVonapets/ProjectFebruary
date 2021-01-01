#pragma once
#include <SDL.h>
#include "globalVariables.h"

class GameWindow
{
public:
	GameWindow();
	bool init();
	void handleEvent(SDL_Event &e);
	void focus();
	void free();

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

	bool hasMouseFocus() { return mMouseFocus; }
	bool hasKeyboardFocus() { return mKeyboardFocus; }
	bool isMinimized() { return mMinimized; }
	bool isShown() { return mShown; }
	
	SDL_Renderer *mRenderer;
private:
	SDL_Window *mWindow;
	
	int mWindowID;

	int mWidth;
	int mHeight;

	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullscreen;
	bool mMinimized;
	bool mShown;
};

