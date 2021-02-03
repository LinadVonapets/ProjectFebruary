#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h> // Раскомментировать, если необходим текст
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

namespace item
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
	item::ItemTypes type;
};


// Инициализация аудио переменных
	// Музыка, которая будет играть
extern Mix_Music *gMusic;
//Саунд эффекты, которые будут использоваться
extern Mix_Chunk *gScratch;
extern Mix_Chunk *gHigh;
extern Mix_Chunk *gMedium;
extern Mix_Chunk *gLow;

//Джойстик захватчик
extern SDL_Joystick *gGameController;
//Тактильная отдача контроллера
extern SDL_Haptic *gControllerHaptic;

// Использовавние отрисовщика и окна в нескольких файлах
extern GameWindow gWindow;

#if defined(SDL_TTF_MAJOR_VERSION)
extern TTF_Font *gFont;
extern TTF_Font *gFont12;
#endif

//Инициализация SDL2
bool Init();

// Загрузка медиа
bool loadMedia();

// Освобождение
void close();

// Функционал loadMedia() и Init() в одной функции
bool LMAI();

//Проверка столкновений
bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);



