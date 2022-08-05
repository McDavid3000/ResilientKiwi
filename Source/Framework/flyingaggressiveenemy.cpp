// This include:
#include "flyingaggressiveenemy.h"

// Local includes:
#include "vector2.h"
#include "sprite.h"
#include "texture.h"
#include "logmanager.h"
#include "playstate.h"
#include "player.h"

// Library includes


FlyingAggressiveEnemy::FlyingAggressiveEnemy()
: m_paceDirection(RIGHT)
, m_prevPos(GetPosition().x)
{
	m_hitpoints = 200;
	m_movementSpeedCategory = FAST;

	AggressiveEnemy::AggressiveEnemy();
}

void
FlyingAggressiveEnemy::Process(float deltaTime)
{
	AggressiveEnemy::Process(deltaTime);
}

void
FlyingAggressiveEnemy::Draw(BackBuffer& backBuffer)
{
	AggressiveEnemy::Draw(backBuffer);
}


void
FlyingAggressiveEnemy::ProcessAI(float deltaTime)
{
	float screenWidth = 480.0f;

	switch (m_pCurrentAIState)
	{
	case AIState::PACING:

		//Move in the direction set
		if (m_paceDirection == LEFT)
		{
			m_velocity = Vector2((float)-GetMovementSpeed(), 0);
		}
		else if (m_paceDirection == RIGHT)
		{
			m_velocity = Vector2((float)GetMovementSpeed(), 0);
		}

		//Check screen bounds
		if (GetPosition().x <= 0)
		{
			//Turn right
			m_paceDirection = RIGHT;
		}
		else if (GetPosition().x >= (screenWidth - m_pSprite->GetWidth()))
		{
			//Turn left
			m_paceDirection = LEFT;
		}

		//Check if texture needs to be flipped
		if (m_prevPos - GetPosition().x > 0)
		{
			m_pSprite->GetTexture()->FlipTexture(true);
		}
		else
		{
			m_pSprite->GetTexture()->FlipTexture(false);
		}
		m_prevPos = GetPosition().x;

		break;
	}

	AggressiveEnemy::ProcessAI(deltaTime);
}