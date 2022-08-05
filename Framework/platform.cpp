// This include:
#include "platform.h"

// Local includes:
#include "spritemanager.h"
#include "sprite.h"
#include "backbuffer.h"

// Library includes


Platform::Platform()
{
	
}

Platform::~Platform()
{

}

bool Platform::Initialise(Vector2 position, int width, int height)
{
	m_relativePos = position;
	m_position = position;
	m_width = width;
	m_height = height;

	if (width == 30)
	{
		m_pSprite = SpriteManager::CreateSpriteFromSheet("assets//PlatformSpriteSheet.png", 0, 0, width, 30);
	}
	else
	{
		m_pSprite = SpriteManager::CreateSpriteFromSheet("assets//PlatformSpriteSheet.png", 0, width-30, width, 30);
	}
	
	return true;
}

bool Platform::Initialise(Sprite* sprite)
{
	//TODO: Implement sprite platform.
	return false;
}

void Platform::Process(float deltaTime)
{
	
}

void Platform::Draw(BackBuffer& backBuffer)
{
	if (!IsDead())
	{
		if (m_pSprite != nullptr)
		{
			backBuffer.DrawFromSpriteSheet(*m_pSprite, m_position.GetXi(), m_position.GetYi());
		}
		else {
			backBuffer.SetDrawColour(Colour(0, 255, 0));
			backBuffer.DrawRectangle(m_position.GetXi(), m_position.GetYi(), m_position.GetXi() + m_width, m_position.GetYi() + m_height);
		}
	}
}

void Platform::UpdatePosition(Vector2 position)
{
	m_position += position;
}

void Platform::ResetPosition(Vector2 sectionPosition)
{
	m_position = sectionPosition + m_relativePos;
}

void Platform::SetRelativePosition(Vector2 position)
{
	m_position = position;
	m_relativePos = position;
}

Vector2 Platform::GetRelativePosition()
{
	return m_relativePos;
}

bool Platform::IsCollidingWith(Entity& e)
{
	if (!IsDead())
	{
		//Rectangle collision detection
		//Is the right edge of platform to the right of the left edge of player rectangle?
		//Is the left edge of platform to the left of the right edge of the player rectangle?
		//Is the bottom edge of this rectangle below the top edge of player?
		//Is the top edge of this rectangle above the bottom edge of player?
		//If all applies, they are colliding
		int platformX = m_position.GetXi();
		int platformY = m_position.GetYi();
		int platformW = m_width;
		int platformH = m_height;

		int foreignX = e.GetPosition().GetXi();
		int foreignY = e.GetPosition().GetYi();
		int foreignW = e.GetWidth();
		int foreignH = e.GetHeight();

		if (platformX + platformW >= foreignX &&
			platformX <= foreignX + foreignW &&
			platformY + platformH >= foreignY &&
			platformY <= foreignY + foreignH)
		{
			return true;
		}

		return false;
	}
	return false;
}

bool Platform::IsCollidingWith(int x, int y, int w, int h)
{
	if (!IsDead())
	{
		int platformX = m_position.GetXi();
		int platformY = m_position.GetYi();
		int platformW = m_width;
		int platformH = m_height / 5; //Need to only check the top third of the platform

		if (platformX + platformW >= x &&
			platformX <= x + w &&
			platformY + platformH >= y &&
			platformY <= y + h)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

int Platform::GetWidth()
{
	return m_width;
}

int Platform::GetHeight()
{
	return m_height;
}

void Platform::ResetPlatform()
{
	SetDead(false);
}