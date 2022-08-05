// This include:
#include "groundpassiveenemy.h"

// Local includes:
#include "platform.h"
#include "vector2.h"
#include "sprite.h"

// Library includes


GroundPassiveEnemy::GroundPassiveEnemy()
: m_paceDirection(LEFT)
, m_pStandingPlatform(0)
{
	m_hitpoints = 120;
	m_movementSpeedCategory = SLOW;

	PassiveEnemy::PassiveEnemy();
}

void 
GroundPassiveEnemy::Process(float deltaTime)
{
	//Keep enemy on its platform (especially with moving platforms)
	if (m_pStandingPlatform != nullptr) //If its platform has been found...
	{
		float standingPositionY = m_pStandingPlatform->GetPosition().y - m_pSprite->GetHeight();
		SetPositionY(standingPositionY);
	}

	PassiveEnemy::Process(deltaTime);
}

void 
GroundPassiveEnemy::Draw(BackBuffer& backBuffer)
{

	PassiveEnemy::Draw(backBuffer);
}


void
GroundPassiveEnemy::ProcessAI(float deltaTime)
{
	//Simple AI - only pacing
	//Need to figure out a way to check collision with the platform underneath enemy
	//Ground enemies probably need a list of all the platforms in the section

	//First find the platform the enemy is standing on if not found already
	if (m_pStandingPlatform == NULL)
	{

		for (auto platform : m_pSectionPlatforms)
		{
			int platformSize = platform->GetHeight();
			if (((platform->GetPosition().y) - (GetPosition().y + GetHeight())) < platformSize)
			{
				m_pStandingPlatform = platform;
			}
		}
	}
	else //Platform already found
	{
		if (m_pStandingPlatform != 0)
		{
			int platformSize = m_pStandingPlatform->GetHeight();

			if (platformSize > 0)
			{
				//Check the collision beneath the enemy, inverted
				int leftBoxX = (int)GetPosition().x - platformSize;
				int leftBoxY = (int)GetPosition().y + m_pSprite->GetHeight();
				int rightBoxX = (int)GetPosition().x + m_pSprite->GetWidth();
				int rightBoxY = leftBoxY;

				bool leftCollidingWithPlatform = m_pStandingPlatform->IsCollidingWith(leftBoxX, leftBoxY, platformSize, platformSize);
				bool rightCollidingWithPlatform = m_pStandingPlatform->IsCollidingWith(rightBoxX, rightBoxY, platformSize, platformSize);


				if (!leftCollidingWithPlatform)
				{
					//If no collision with left side, then enemy needs to move right
					m_paceDirection = RIGHT;
				}
				else if (!rightCollidingWithPlatform)
				{
					//If no collision with right side, then enemy needs to move left
					m_paceDirection = LEFT;
				}
			}
		}

		switch (m_paceDirection)
		{
		case RIGHT:
			m_velocity = Vector2((float)GetMovementSpeed(), 0);
			break;
		case LEFT:
			m_velocity = Vector2((float)-GetMovementSpeed(), 0);
			break;
		}
	}

}