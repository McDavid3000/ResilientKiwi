#pragma once
#include <SDL_pixels.h>

#include "interfacecomponent.h"
class Sprite;

class Rectangle : public InterfaceComponent
{
public:
	Rectangle();
	~Rectangle();

	void Rectangle::Initialise(Vector2 position, int width, int height);
	void DrawFromCenter(bool drawFromCenter);
	void SetBackgroundSprite(Sprite* sprite);
	void DrawRectangle(BackBuffer& backBuffer, int startX, int startY);
	void Draw(BackBuffer& backBuffer) override;
	Vector2 GetPosition();
	Vector2 GetCenter();
	int GetWidth();
	int GetHeight();
	
protected:
private:

public:
protected:
	Vector2 m_center;
	int m_width;
	int m_height;
	Sprite* m_pBackgroundSprite;
	SDL_Color m_colour;
	bool m_DrawFromCenter;
private:
	
};

