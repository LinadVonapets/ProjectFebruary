#include "EngineCore.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

GameWindow gWindow;
//������������� ����������� � ����
//������������� ���������
SDL_Joystick *gGameController{ nullptr };
SDL_Haptic *gControllerHaptic{ nullptr };

// ������������� ����� ����������
	// ������, ������� ����� ������
Mix_Music *gMusic{ nullptr };
	//����� �������, ������� ����� ��������������
Mix_Chunk *gScratch{ nullptr };
Mix_Chunk *gHigh{ nullptr };
Mix_Chunk *gMedium{ nullptr };
Mix_Chunk *gLow{ nullptr };


#if defined(SDL_TTF_MAJOR_VERSION)
TTF_Font *gFont{ nullptr };
TTF_Font *gFont12{ nullptr };
#endif


bool debug_mode = false;
bool plyrShwPos = false;

std::string levelNumAndName[2] = { "\"Level Name\"", "Level 0" };


bool checkCollision(const SDL_Rect &a, const SDL_Rect &b)
{
	int topA, topB;
	int leftA, leftB;
	int rightA, rightB;
	int bottomA, bottomB;

	topA = a.y;
	leftA = a.x;
	rightA = a.x + a.w;
	bottomA = a.y + a.h;

	topB = b.y;
	leftB = b.x;
	rightB = b.x + b.w;
	bottomB = b.y + b.h;

	if (topA >= bottomB)
		return false;
	if (bottomA <= topB)
		return false;
	if (leftA >= rightB)
		return false;
	if (rightA <= leftB)
		return false;
	return true;
	
}

// ������������� SDL2 � � �����������
bool Init()
{
	bool success = true;

	//������������� �������� PNG
	int imgFlags = IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO /*| SDL_INIT_JOYSTICK*/  /*| SDL_INIT_HAPTIC*/) < 0) // ������������� SDL
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else if (!(IMG_Init(imgFlags) & imgFlags)) // ������������� SDL_image
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}
	else if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
#if defined(SDL_TTF_MAJOR_VERSION)
	else if (TTF_Init() == -1) // ������������� SDL_ttf
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
#endif
	else
	{
		if (!gWindow.init())
		{
			success = false;
		}
	}

	// �� �������� �������, ����� ����������� � ���!!!
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!\n");
	}

	//����� ����������
	if (SDL_NumJoysticks() == 0)
	{
		SDL_Log("No joystick connected!\n");
	}
	else
	{
		std::cout << SDL_NumJoysticks() << " number of gamepads\n";
		//�������� ���������
		gGameController = SDL_JoystickOpen(1);
		if (gGameController == nullptr)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//��������� ���������� ���������� ������
			gControllerHaptic = SDL_HapticOpenFromJoystick(gGameController);
			if (gControllerHaptic == nullptr)
			{
				printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				if (SDL_HapticRumbleInit(gControllerHaptic) < 0)
				{
					printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
				}
			}

		}
	}

	return success;
}



// ������������ �����
void close()
{
	
	//Free the sound effects
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = nullptr;
	gHigh = nullptr;
	gMedium = nullptr;
	gLow = nullptr;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	SDL_HapticClose(gControllerHaptic);
	SDL_JoystickClose(gGameController);
	gControllerHaptic = nullptr;
	gGameController = nullptr;


#if defined(SDL_TTF_MAJOR_VERSION)
	TTF_CloseFont(gFont);
	gFont = nullptr;
#endif

	gWindow.free();

#if defined(SDL_TTF_MAJOR_VERSION)
	TTF_Quit();
#endif
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool LMAI()
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
		return false;
	}
	else if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return false;
	}
	return true;
}

