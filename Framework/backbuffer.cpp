// COMP710 GP 2D Framework 2020

// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "texturemanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "texture.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <SDL_ttf.h>

BackBuffer::BackBuffer()
: m_pTextureManager(0)
, m_pWindow(0)
, m_pRenderer(0)
, m_width(0)
, m_height(0)
, m_clearRed(0)
, m_clearGreen(0)
, m_clearBlue(0)
{

}

BackBuffer::~BackBuffer()
{
	//Close font
	TTF_CloseFont(m_pFont);

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	delete m_pTextureManager;
	m_pTextureManager = nullptr;

	IMG_Quit();
	SDL_Quit();
}

bool 
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("RKMD: Resilient Kiwi, Magnificent Dreams", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
			}
		}
	}

	SetFullscreen(false);
	SDL_Delay(1000);
	
	//Enable alpha blending
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
	
	TTF_Init();

	//Create font
	int fontSize = 20;
	m_pFont = TTF_OpenFont("assets\\arial.ttf", fontSize);

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	return (true);
}

void 
BackBuffer::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
//		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
		SDL_SetWindowSize(m_pWindow, m_width, m_height);
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, 0);
	}
}

void 
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void BackBuffer::SetDrawColour(Colour colour)
{
	SetDrawColour(colour.m_red, colour.m_green, colour.m_blue, colour.m_alpha);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void BackBuffer::SetTextColour(Colour colour)
{
	SetTextColour(colour.m_red, colour.m_green, colour.m_blue, colour.m_alpha);
}

void BackBuffer::SetTextColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetTextColour(r, g, b, 255);
}

void BackBuffer::SetTextColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_textColour.r = r;
	m_textColour.g = g;
	m_textColour.b = b;
	m_textColour.a = a;
}

void 
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), sprite.GetAlpha());

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, sprite.GetTexture()->GetRotation(), 0, sprite.GetTexture()->GetFlip());
}

void 
BackBuffer::DrawSpritePortion(Sprite& sprite, int x, int y, int w, int h)
{
	SDL_Rect src;
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;

	//Ensures no stretching of the image when drawing the last portions
	int screenHeight = 854;
	int buffer = 0;
	if (y < screenHeight)
	{
		buffer = screenHeight - y;
	}
	else if (y >= sprite.GetHeight() - h)
	{
		buffer = (sprite.GetHeight() - h) - y;
	}

	SDL_Rect dest;
	dest.x = sprite.GetX();
	dest.y = sprite.GetY() + buffer;
	dest.w = w;
	dest.h = h;

	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), sprite.GetAlpha());
	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), &src, &dest);
}

void 
BackBuffer::DrawAnimatedSprite(AnimatedSprite& sprite, int frames)
{
	SDL_Rect dest, src;

	src.x = frames;
	//call sprites Y value getter
	src.y = sprite.GetSpriteRow();
	src.w = sprite.GetFrameWidth();
	src.h = sprite.GetFrameHeight();

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetFrameWidth();
	dest.h = sprite.GetFrameHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), &src, &dest);
}

void BackBuffer::DrawFromSpriteSheet(Sprite& sprite, int destX, int destY)
{
	SDL_Rect dest, src;

	src.x = sprite.GetX();
	src.y = sprite.GetY();
	src.w = sprite.GetWidth();
	src.h = sprite.GetHeight();

	dest.x = destX;
	dest.y = destY;
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), &src, &dest);
}


void BackBuffer::DrawText(int x, int y, TTF_Font* font, const char* pcText)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_Surface* surface = TTF_RenderText_Blended(font, pcText, m_textColour);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

	//Renderer, the text (think of the text like an image), cropping rect, text rectangle (think of like a text box)
	SDL_RenderCopy(m_pRenderer, texture, NULL, &destRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

}
void BackBuffer::DrawText(int x, int y, const char* pcText)
{
	DrawText(x, y, m_pFont, pcText); //Call above method but with pre-created font
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;
	
	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2 - x1;
	fillRect.h = y2 - y1;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void 
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite* 
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

void 
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}

