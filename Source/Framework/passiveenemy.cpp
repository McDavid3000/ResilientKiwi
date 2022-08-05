// This include:
#include "passiveenemy.h"

// Local includes:


// Library includes


PassiveEnemy::PassiveEnemy()
{
	Enemy::Enemy();
}

void PassiveEnemy::Process(float deltaTime)
{
	Enemy::Process(deltaTime);
}

void PassiveEnemy::Draw(BackBuffer& backBuffer)
{
	Enemy::Draw(backBuffer);
}