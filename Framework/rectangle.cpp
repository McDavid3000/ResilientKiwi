#include "rectangle.h"
#include "backbuffer.h"

#include "sprite.h"


Rectangle::Rectangle()
{
	//Rectangle Colour
	m_pBackgroundSprite = nullptr;
	m_DrawFromCenter = false;
}

Rectangle::~Rectangle()
{
	//Disable this as it is managed by spritemanager
	// delete m_pBackgroundSprite;
	// m_pBackgroundSprite = nullptr;
}

void Rectangle::Initialise(Vector2 position, int width, int height)
{
	m_position = position;
	m_center = Vector2(position.x - width / 2, position.y - height / 2);
	m_width = width;
	m_height = height;
}

void Rectangle::Draw(BackBuffer& backBuffer)
{
	if (m_visible)
	{
		if (m_DrawFromCenter)
		{
			if (m_pBackgroundSprite != nullptr)
			{
				//DRAW BACKGROUND SPRITE
				//backBuffer.DrawSprite(*m_pBackgroundSprite);
				backBuffer.DrawFromSpriteSheet(*m_pBackgroundSprite, m_position.GetXi(), m_position.GetYi());

			}
			else
			{
				//DRAW COLOURED REC
				DrawRectangle(backBuffer, m_position.GetXi(), m_position.GetYi());
			}
		}
		else
		{
			if (m_pBackgroundSprite != nullptr)
			{
				//DRAW BACKGROUND RECT
				//backBuffer.DrawSprite(*m_pBackgroundSprite);
				backBuffer.DrawFromSpriteSheet(*m_pBackgroundSprite, m_position.GetXi(), m_position.GetYi());
			}
			else
			{
				//DRAW COLOURED REC
				DrawRectangle(backBuffer, m_position.GetXi(), m_position.GetYi());
			}
		}
	}
}

void Rectangle::DrawRectangle(BackBuffer& backBuffer, int startX, int startY)
{
	backBuffer.SetDrawColour(m_enabled ? m_primaryColour : m_primaryColourDisabled);
	backBuffer.DrawRectangle(startX, startY, startX + m_width, startY + m_height);
}


void Rectangle::SetBackgroundSprite(Sprite* sprite)
{
	m_pBackgroundSprite = sprite;
	// m_pBackgroundSprite->SetX(m_position.GetXi());
	// m_pBackgroundSprite->SetY(m_position.GetYi());
	m_width = sprite->GetWidth();
	m_height = sprite->GetHeight();
}

Vector2 Rectangle::GetPosition()
{
	return m_position;
}

Vector2 Rectangle::GetCenter()
{
	return m_center;
}

int Rectangle::GetWidth()
{
	return m_width;
}

int Rectangle::GetHeight()
{
	return m_height;
}


void Rectangle::DrawFromCenter(bool drawFromCenter)
{
	m_DrawFromCenter = drawFromCenter;
	
	if (drawFromCenter)
	{
		m_center = m_position;
		m_position.x -= m_width / 2;
		m_position.y -= m_height / 2;
	}
	else
	{
		m_position = m_center;
	}
}




