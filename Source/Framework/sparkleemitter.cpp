#include "sparkleemitter.h"
#include "backbuffer.h"
#include "spritemanager.h"

SparkleEmitter::SparkleEmitter()
	:m_timeElapsed(0)
{
}

SparkleEmitter::~SparkleEmitter()
{
}

void
SparkleEmitter::InitialiseParticles()
{
	bool init;

	m_sparkleArrSize = sizeof(m_arrSparkles) / sizeof(m_arrSparkles[0]);

	for (int i = 0; i < m_sparkleArrSize; i++)
	{
		if (!m_arrSparkles[i].Initialise(SpriteManager::CreateSprite("assets/sparkle1.png")))
		{
			init = false;
		}
		m_arrSparkles[i].SetDead(true);
	}
}

void
SparkleEmitter::Process(float deltaTime)
{
	m_timeElapsed += deltaTime;
	if (m_timeElapsed > .3f)
	{
		SpawnParticles();
		m_timeElapsed = 0;
	}

	for (int i = 0; i < m_sparkleArrSize; i++)
	{
		m_arrSparkles[i].Process(deltaTime);
		m_arrSparkles[i].SetAlpha(m_arrSparkles[i].GetAlpha() - 4);

		if (m_arrSparkles[i].GetAlpha() < 10)
		{
			m_arrSparkles[i].SetDead(true);
		}
	}
}

void
SparkleEmitter::Draw(BackBuffer &backBuffer)
{
	for (int i = 0; i < m_sparkleArrSize; i++)
	{
		if (!m_arrSparkles[i].IsDead())
		{
			m_arrSparkles[i].Draw(backBuffer);
		}
	}
}

void
SparkleEmitter::SpawnParticles()
{
	int numParticles = ((rand() % 4) + 1);

	for (int i = 0; i < numParticles; i++)
	{
		if (m_arrSparkles[i].IsDead())
		{
			m_arrSparkles[i].SetDead(false);
			m_arrSparkles[i].SetAlpha(255);
			m_arrSparkles[i].SetVerticalVelocity(-35.0f);
			m_arrSparkles[i].SetHorizontalVelocity(0);
			m_arrSparkles[i].SetPosition(Vector2((this->GetPosition().x + (rand() % 50 + (-25.0f))), this->GetPosition().y));
		}
	}
}

