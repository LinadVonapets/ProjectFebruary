#ifndef _GAME_TEXTURE_
#define _GAME_TEXTURE_

#include "EngineCore.h"

// Класс-оболочка текстуры
class GameTexture
{
public:
	// Инициализация перменных
	GameTexture();

	// Освобождение памяти
	~GameTexture();

	// Загрузка картинки по заданному пути
	bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	// Создаёт картинку из строки шрифта
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font=gFont);
#endif

	// Освобождение текстур
	void free();

	//Установка модуляции цвета
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Установка смешивания
	void setBlendMode(SDL_BlendMode blending);

	//Установка модуляции альфа-цвета
	void setAlpha(Uint8 alpha);

	// Отрисовка текстуры в заданной точке
	void render(int x, int y, int w = NULL, int h = NULL, SDL_Rect *clip = nullptr,
		double angle = 0.0, SDL_Point *center = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Получение размеров картинки
	int getWidth();
	int getHeight();

private:
	// Непосредственно текстура
	SDL_Texture *mTexture;

	// Размеры картинки
	int mWidth;
	int mHeight;
};

#endif