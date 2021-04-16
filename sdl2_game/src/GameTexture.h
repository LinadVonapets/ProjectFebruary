#ifndef _GAME_TEXTURE_
#define _GAME_TEXTURE_

#include "EngineCore.h"

// �����-�������� ��������
class GameTexture
{
public:
	// ������������� ���������
	GameTexture();

	// ������������ ������
	~GameTexture();

	// �������� �������� �� ��������� ����
	bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	// ������ �������� �� ������ ������
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font=gFont);
#endif

	// ������������ �������
	void free();

	//��������� ��������� �����
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//��������� ����������
	void setBlendMode(SDL_BlendMode blending);

	//��������� ��������� �����-�����
	void setAlpha(Uint8 alpha);

	// ��������� �������� � �������� �����
	void render(int x, int y, int w = NULL, int h = NULL, SDL_Rect *clip = nullptr,
		double angle = 0.0, SDL_Point *center = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	// ��������� �������� ��������
	int getWidth();
	int getHeight();

private:
	// ��������������� ��������
	SDL_Texture *mTexture;

	// ������� ��������
	int mWidth;
	int mHeight;
};

#endif