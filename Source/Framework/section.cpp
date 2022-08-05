#include "section.h"
#include "pickups.h"
#include "enemyfactory.h"

#include "enemy.h"
#include "groundpassiveenemy.h"
#include "groundaggressiveenemy.h"
#include "flyingaggressiveenemy.h"

#include <typeinfo>
#include <list>

Section::Section()
{
}

Section::~Section()
{
	for (auto m_enemy : m_enemies)
	{
		delete m_enemy;
		m_enemy = nullptr;
	}
	for (auto m_platform : m_platforms)
	{
		delete m_platform;
		m_platform = nullptr;
	}
	for (auto pickup : m_pickUps)
	{
		delete pickup;
		pickup = nullptr;
	}
}

void Section::Initialise(Vector2(position))
{
	m_position = position;

	for (auto platform : m_platforms)
	{
		
	}
}

void Section::Process(float deltaTime)
{
	//Process enemies by their type to get the level skin
	for (auto gpEnemy : m_gpEnemies)
	{
		EnemyFactory::GetInstance().ProcessCurrentGroundPassiveEnemy(gpEnemy);
	}
	for (auto gaEnemy : m_gaEnemies)
	{
		EnemyFactory::GetInstance().ProcessCurrentGroundAggressiveEnemy(gaEnemy);
	}
	for (auto faEnemy : m_faEnemies)
	{
		EnemyFactory::GetInstance().ProcessCurrentFlyingAggressiveEnemy(faEnemy);
	}
	//Process enemies normally
	for (auto enemy : m_enemies)
	{
		enemy->Process(deltaTime);
	}

	for (auto m_platform : m_platforms)
	{
		m_platform->Process(deltaTime);
	}

	for (auto pickup : m_pickUps)
	{
		pickup->Process(deltaTime);
	}
}

void Section::Draw(BackBuffer& backBuffer)
{
	for (auto m_platform : m_platforms)
	{
		m_platform->Draw(backBuffer);
	}
	for (auto m_enemy : m_enemies)
	{
		m_enemy->Draw(backBuffer);
	}
	for (auto pickup : m_pickUps)
	{
		pickup->Draw(backBuffer);
	}
}

void Section::AddPlatform(Platform* platform)
{
	m_platforms.push_back(platform);
}

void Section::AddPlatforms(std::list<Platform*> platforms)
{
	m_platforms = platforms;
}

void Section::AddEnemies(std::list<Enemy*> enemies)
{
	m_enemies = enemies;
}

void Section::AddPickUps(std::list<PickUps*> pickUps)
{
	m_pickUps = pickUps;
}

std::list<Platform*> Section::GetPlatforms()
{
	return m_platforms;
}

std::list<Enemy*> Section::GetEnemies()
{
	return m_enemies;
}

Vector2 Section::GetPosition()
{
	return m_position;
}

void Section::SetPosition(Vector2 position)
{
	m_position = position;
	
	//Set entity position
	for (auto platform : m_platforms)
	{
		platform->ResetPosition(position);
	}
	for (auto enemy : m_enemies)
	{
		enemy->ResetPosition(position);
	}

	for (auto pickup : m_pickUps)
	{
		pickup->ResetPosition(position);
	}
}

void Section::UpdatePosition(Vector2 position)
{
	//Update this sections position
	m_position += position;

	//Update entity position
	for (auto platform : m_platforms)
	{
		platform->UpdatePosition(position);
	}
	for (auto enemy : m_enemies)
	{
		enemy->UpdatePosition(position);
	}
	for (auto pickup : m_pickUps)
	{
		pickup->UpdatePosition(position);
	}	
}

void 
Section::CheckPickUpCollisions(Player* player)
{
	for (auto pickup : m_pickUps)
	{
		pickup->CheckPlayerCollision(player);
	}
}

void
Section::RenewPickUps()
{
	for (auto pickup : m_pickUps)
	{
		pickup->SetDead(false);
	}
}

void
Section::RenewEnemies()
{
	for (auto enemy : m_enemies)
	{
		enemy->SetDead(false);
		enemy->SetAIState(Enemy::AIState::PACING);
	}
}

void
Section::RenewPlatforms()
{
	for (auto platform : m_platforms)
	{
		platform->ResetPlatform();
	}
}

void 
Section::AddGPEnemies(std::list<GroundPassiveEnemy*> gpEnemies)
{
	m_gpEnemies = gpEnemies;
}
void 
Section::AddGAEnemies(std::list<GroundAggressiveEnemy*> gaEnemies)
{
	m_gaEnemies = gaEnemies;
}
void 
Section::AddFAEnemies(std::list<FlyingAggressiveEnemy*> faEnemies)
{
	m_faEnemies = faEnemies;
}