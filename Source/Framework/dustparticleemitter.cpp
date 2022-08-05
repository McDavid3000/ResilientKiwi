#include "dustparticleemitter.h"
#include "backbuffer.h"
#include "spritemanager.h"

DustParticleEmitter::DustParticleEmitter()
{
}

DustParticleEmitter::~DustParticleEmitter()
{
}

void
DustParticleEmitter::InitialiseParticles()
{
	bool init;

	m_dustParticlesArrSize = sizeof(m_arrDustParticles) / sizeof(m_arrDustParticles[0]);

	for (int i = 0; i < m_dustParticlesArrSize; i++)
	{
		if (!m_arrDustParticles[i].Initialise(SpriteManager::CreateSprite("assets/dustparticle.png")))
		{
			init = false;
		}
	}
}

void
DustParticleEmitter::Process(float deltaTime)
{
	for (int i = 0; i < m_dustParticlesArrSize; i++)
	{
			m_arrDustParticles[i].Process(deltaTime);
			m_arrDustParticles[i].SetAlpha(m_arrDustParticles[i].GetAlpha() - 6);

			if (m_arrDustParticles[i].GetAlpha() < 10)
			{
				m_arrDustParticles[i].SetDead(true);
			}
	}
}

void
DustParticleEmitter::Draw(BackBuffer &backBuffer)
{
	for (int i = 0; i < m_dustParticlesArrSize; i++)
	{
		if (!m_arrDustParticles[i].IsDead())
		{
			m_arrDustParticles[i].Draw(backBuffer);
		}
	}
}

void
DustParticleEmitter::SpawnParticles()
{
	for (int i = 0; i < m_dustParticlesArrSize; i++)
	{
		m_arrDustParticles[i].SetDead(false);
		m_arrDustParticles[i].SetAlpha(255);
		m_arrDustParticles[i].SetVerticalVelocity(float(rand() % 100) - 50);
		m_arrDustParticles[i].SetHorizontalVelocity(float(rand() % 100) - 50);
		m_arrDustParticles[i].SetPosition(this->GetPosition());
	}
}

