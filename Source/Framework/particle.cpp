#include "particle.h"
#include "backbuffer.h"
#include "sprite.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Process(float deltaTime)
{
	m_position.x = m_position.x + (deltaTime * m_velocity.x);
	m_position.y = m_position.y + (deltaTime * m_velocity.y);
}

void Particle::SetAlpha(unsigned char alpha)
{
	m_pSprite->SetAlpha(alpha);
}

unsigned char Particle::GetAlpha()
{
	return m_pSprite->GetAlpha();
}



