// COMP710 GP 2D Framework 2020

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_position(0, 0)
, m_velocity(0, 0)
, m_dead(false)
{

}

Entity::~Entity()
{
	
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void 
Entity::Process(float deltaTime)
{

}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	return (false);
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

Vector2
Entity::GetPosition() const
{
	return (m_position);
}

void
Entity::SetPosition(Vector2 position)
{
	m_position = position;
}


void
Entity::SetPositionX(float x)
{
	m_position.x = x;
}

void
Entity::SetPositionY(float y)
{
	m_position.y = y;
}

Vector2
Entity::GetVelocity() const
{
	return (m_velocity);
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocity.x);
}

void Entity::SetVelocity(Vector2 velocity)
{
	m_velocity = velocity;
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocity.y);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocity.x = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocity.y = y;
}

bool 
Entity::IsDead() const
{
	return (m_dead);
}

void
Entity::SetAlpha(unsigned char alpha)
{
	m_pSprite->SetAlpha(alpha);
}

unsigned char
Entity::GetAlpha()
{
	return m_pSprite->GetAlpha();
}

int
Entity::GetWidth() 
{
	return (m_pSprite->GetWidth());
}

int
Entity::GetHeight() 
{
	return (m_pSprite->GetHeight());
}

Sprite * Entity::GetSprite()
{
	return m_pSprite;
}

//returns the position of the centre of the sprite
Vector2 Entity::GetCentrePosition()
{
	m_centerPosition.x = m_position.x + (m_pSprite->GetWidth() / 2);
	m_centerPosition.y = m_position.y + (m_pSprite->GetHeight() / 2);

	return m_centerPosition;
}
