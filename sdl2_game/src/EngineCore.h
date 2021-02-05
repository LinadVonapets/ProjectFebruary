#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h> // �����������������, ���� ��������� �����
#include <cmath>
#include <sstream>
#include <vector> 
#include <array>
#include <fstream>
#include "globalVariables.h"
#include "GameWindow.h"
#include <nlohmann/json.hpp>

extern std::string levelNumAndName[2];
extern bool debug_mode;
extern bool plyrShwPos;

namespace itemNamespace
{
	enum ItemTypes
	{
		EMPTY,
		KEY,
		APPLE,
		SWORD,
		TOTAL,
	};
}

struct Item
{
	SDL_Rect collider;
	itemNamespace::ItemTypes type;
};


// ������������� ����� ����������
	// ������, ������� ����� ������
extern Mix_Music *gMusic;
//����� �������, ������� ����� ��������������
extern Mix_Chunk *gScratch;
extern Mix_Chunk *gHigh;
extern Mix_Chunk *gMedium;
extern Mix_Chunk *gLow;

//�������� ���������
extern SDL_Joystick *gGameController;
//���������� ������ �����������
extern SDL_Haptic *gControllerHaptic;

// �������������� ����������� � ���� � ���������� ������
extern GameWindow gWindow;

#if defined(SDL_TTF_MAJOR_VERSION)
extern TTF_Font *gFont;
extern TTF_Font *gFont12;
#endif

//������������� SDL2
bool Init();

// �������� �����
bool loadMedia();

// ������������
void close();

// ���������� loadMedia() � Init() � ����� �������
bool LMAI();

//�������� ������������
bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);



