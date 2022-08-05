#include "movingplatform.h"

#include "backbuffer.h"
#include "spritemanager.h"

MovingPlatform::MovingPlatform()
{
	m_velocity = Vector2(0, 0);
}

MovingPlatform::~MovingPlatform()
{
}

bool MovingPlatform::Initialise(Vector2 positionOne, Vector2 positionTwo, int width, int height)
{
	m_position = positionOne;
	m_width = width;
	m_height = height;
	m_firstPosition = positionOne;
	m_secondPosition = positionTwo;
	
	int sheetStart = 180;
	if (width == 30)
	{
		m_pSprite = SpriteManager::CreateSpriteFromSheet("assets//PlatformSpriteSheet.png", 0, sheetStart, width, 30);
	}
	else
	{
		m_pSprite = SpriteManager::CreateSpriteFromSheet("assets//PlatformSpriteSheet.png", 0, sheetStart + width, width, 30);
	}
	
	return true;
}

bool MovingPlatform::Initialise(Sprite* sprite)
{
	//TODO: Implement sprite platform.
	return false;
}

void MovingPlatform::Process(float deltaTime)
{
	m_position += (m_velocity * deltaTime); //Move platform

	//Change direction if reached end point
	if (m_currentDirection == UP)
	{
		if (m_position.y < m_secondPosition.y)
			SetDirection(DOWN);
	}
	else if (m_currentDirection == DOWN)
	{
		if (m_position.y > m_firstPosition.y)
			SetDirection(UP);
	}
	else if (m_currentDirection == LEFT)
	{
		if (m_position.x < m_firstPosition.x)
			SetDirection(RIGHT);
	}
	else if (m_currentDirection == RIGHT)
	{
		if (m_position.x > m_secondPosition.x)
			SetDirection(LEFT);
	}
}

void MovingPlatform::Draw(BackBuffer& backBuffer)
{
	if (m_pSprite != nullptr)
	{
		backBuffer.DrawFromSpriteSheet(*m_pSprite, m_position.GetXi(), m_position.GetYi());
	}
	else {

		backBuffer.SetDrawColour(Colour(0, 255, 255));
		backBuffer.DrawRectangle(m_position.GetXi(), m_position.GetYi(), m_position.GetXi() + m_width, m_position.GetYi() + m_height);
	}
}

void MovingPlatform::ResetPosition(Vector2 sectionPosition)
{
	m_position = sectionPosition + m_relativePos;
	
	if (m_currentDirection == UP || m_currentDirection == DOWN)
	{
		m_firstPosition = sectionPosition + m_relativePos;
		m_secondPosition = Vector2(m_firstPosition.x, m_firstPosition.y - 210);
	}
}

void MovingPlatform::UpdatePosition(Vector2 position)
{
	m_position += position;
	m_firstPosition += position;
	m_secondPosition += position;
}

bool MovingPlatform::IsCollidingWith(Entity& e)
{
	return false;
}

void MovingPlatform::SetDirection(Direction direction)
{
	m_currentDirection = direction;
	
	if (m_currentDirection == UP)
	{
		m_velocity.Set(0, -75);
	}
	else if (m_currentDirection == DOWN)
	{
		m_velocity.Set(0, 75);
	}
	else if (m_currentDirection == LEFT)
	{
		m_velocity.Set(-75, 0);
	}
	else if (m_currentDirection == RIGHT)
	{
		m_velocity.Set(75, 0);
	}
}
