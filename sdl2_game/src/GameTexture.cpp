#include "GameTexture.h"

// Методы класс GameTexture
GameTexture::GameTexture()
{
	// Инициализация
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

GameTexture::~GameTexture()
{
	// Освобождение
	free();
}

bool GameTexture::loadFromFile(std::string path)
{
	free();

	// Финальная текстура
	SDL_Texture *newTexture{ nullptr };

	// Загрузка изображения по указанному пути
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xff, 0xff));

		newTexture = SDL_CreateTextureFromSurface(gWindow.mRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Получение размеров текстуры
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);

	}
	mTexture = newTexture;
	return mTexture != nullptr;
}

void GameTexture::free()
{
	// Освобождение текстуры, если она есть
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void GameTexture::render(int x, int y, int w, int h, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Выделяем место отрисовки
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Установка размеров выреза
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	if (w != NULL && h != NULL)
	{
		renderQuad.w = w;
		renderQuad.h = h;
	}



	//Отрисовка
	SDL_RenderCopyEx(gWindow.mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int GameTexture::getWidth()
{
	return mWidth;
}

int GameTexture::getHeight()
{
	return mHeight;
}

void GameTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Модуляция текстуры
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void GameTexture::setBlendMode(SDL_BlendMode blending)
{
	//Установка функции смешивания
	SDL_SetTextureBlendMode(mTexture, blending);
}

void GameTexture::setAlpha(Uint8 alpha)
{
	//Установка альфа-канала
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool GameTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font)
{
	//Избавляемся от ранее существовавшей текстуры
	free();

	// Отрисовка поверхности с текстом
	SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Создание текстуры из поверхности
		mTexture = SDL_CreateTextureFromSurface(gWindow.mRenderer, textSurface);
		if (mTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != nullptr;
}
#endif
