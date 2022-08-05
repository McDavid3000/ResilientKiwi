// COMP710 GP 2D Framework 2020
#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__
#include <SDL_pixels.h>
#include <SDL_ttf.h>


#include "colour.h"

// Forward Declarations:
class TextureManager;
class Sprite;
class AnimatedSprite;
struct SDL_Window;
struct SDL_Renderer;

class BackBuffer
{
	//Member Methods:
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetFullscreen(bool fullscreen);

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(Colour colour);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetTextColour(Colour colour);
	void SetTextColour(unsigned char r, unsigned char g, unsigned char b);
	void SetTextColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawSprite(Sprite& sprite);
	void DrawSpritePortion(Sprite& sprite, int x, int y, int w, int h);
	
	void DrawAnimatedSprite(AnimatedSprite& sprite, int frames);
	void DrawFromSpriteSheet(Sprite& sprite, int destX, int destY);
	void DrawText(int x, int y, TTF_Font* font, const char* pcText);
	void DrawText(int x, int y, const char* pcText);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);

	Sprite* CreateSprite(const char* pcFilename);
	
protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	//Member Data:
public:

protected:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;

	TTF_Font* m_pFont;

	SDL_Color m_textColour;
	
private:

};

#endif // __BACKBUFFER_H__
