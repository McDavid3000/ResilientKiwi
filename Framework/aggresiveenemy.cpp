// This include:
#include "aggresiveenemy.h"

// Local includes:
#include "playstate.h"
#include "player.h"
#include "sprite.h"
#include "vector2.h"
#include "backbuffer.h"

// Library includes


AggressiveEnemy::AggressiveEnemy()
{
	m_pCurrentAIState = Enemy::AIState::PACING;
	Enemy::Enemy();
}

void AggressiveEnemy::Process(float deltaTime)
{
	Enemy::Process(deltaTime);
}

void 
AggressiveEnemy::ProcessAI(float deltaTime)
{
	if (m_pCurrentAIState == AIState::PACING)
	{
		//Get players radius * 3
		Player* player = PlayState::GetInstance()->GetPlayer();
		int playerX = (int)player->GetPosition().x - player->GetSprite()->GetWidth();
		int playerY = (int)player->GetPosition().y - player->GetSprite()->GetHeight();
		int playerW = player->GetSprite()->GetWidth() * 3;
		int playerH = player->GetSprite()->GetHeight() * 3;

		//Check if player is nearby
		bool inRange = IsCollidingWith(playerX, playerY, playerW, playerH);
		if (inRange)
		{
			m_pCurrentAIState = Enemy::AIState::ATTACKING;
		}
	}
	else
	{
		//Move towards player
		Vector2 newPos = Vector2::Lerp(GetPosition(), PlayState::GetInstance()->GetPlayer()->GetPosition(), deltaTime / 2);
		SetPosition(newPos);
	}

	Enemy::ProcessAI(deltaTime);
}


void AggressiveEnemy::Draw(BackBuffer& backBuffer)
{

	Enemy::Draw(backBuffer);
}