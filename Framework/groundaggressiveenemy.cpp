// This include:
#include "groundaggressiveenemy.h"

// Local includes:
#include "platform.h"
#include "vector2.h"
#include "sprite.h"

// Library includes


GroundAggressiveEnemy::GroundAggressiveEnemy()
	: m_paceDirection(LEFT)
	, m_pStandingPlatform(0)
	, m_currentAIState(PACING)
{
	m_hitpoints = 150;
	m_movementSpeedCategory = MEDIUM;

	AggressiveEnemy::AggressiveEnemy();
}

void
GroundAggressiveEnemy::Process(float deltaTime)
{
	//Keep enemy on its platform (especially with moving platforms)
	if (m_pStandingPlatform != nullptr) //If its platform has been found...
	{
		float standingPositionY = m_pStandingPlatform->GetPosition().y - m_pSprite->GetHeight();
		SetPositionY(standingPositionY);
	}

	AggressiveEnemy::Process(deltaTime);
}

void
GroundAggressiveEnemy::Draw(BackBuffer& backBuffer)
{

	AggressiveEnemy::Draw(backBuffer);
}


void
GroundAggressiveEnemy::ProcessAI(float deltaTime)
{
	//Pacing and attacking states

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
		if (m_currentAIState == PACING)
		{
			int platformSize = m_pStandingPlatform->GetHeight();

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
		else
		{
			int platformSize = m_pStandingPlatform->GetHeight();

			//Check the collision beneath the enemy, inverted
			int leftBoxX = (int)GetPosition().x - platformSize;
			int leftBoxY = (int)GetPosition().y + m_pSprite->GetHeight();
			int rightBoxX = (int)GetPosition().x + m_pSprite->GetWidth();
			int rightBoxY = leftBoxY;

			bool leftCollidingWithPlatform = m_pStandingPlatform->IsCollidingWith(leftBoxX, leftBoxY, platformSize, platformSize);
			bool rightCollidingWithPlatform = m_pStandingPlatform->IsCollidingWith(rightBoxX, rightBoxY, platformSize, platformSize);

			if (leftCollidingWithPlatform && rightCollidingWithPlatform)
			{
				AggressiveEnemy::ProcessAI(deltaTime);
			}
		}
	}

}