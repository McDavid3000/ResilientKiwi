#include "dustparticle.h"

DustParticle::DustParticle()
{
}

DustParticle::~DustParticle()
{
}

void DustParticle::Process(float deltaTime)
{
	m_position.x = m_position.x + (deltaTime * m_velocity.x);
	m_position.y = m_position.y + (deltaTime * m_velocity.y);
}
