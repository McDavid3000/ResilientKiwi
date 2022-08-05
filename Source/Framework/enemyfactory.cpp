// This include:
#include "enemyfactory.h"

// Local includes:
#include "playstate.h"
#include "spritemanager.h"
#include "sprite.h"

#include "groundaggressiveenemy.h"
#include "groundpassiveenemy.h"
#include "flyingaggressiveenemy.h"

// Library includes:


// Static members 
EnemyFactory* EnemyFactory::sm_pInstance = 0;


EnemyFactory::EnemyFactory()
{
	//Create all the enemy sprites
	m_pPossumSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Possum.png");
	m_pRatSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Rat.png");
	m_pSheepSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Sheep.png");
	m_pUnicornSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Unicorn.png");
	m_pFleebSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Fleeb.png");

	m_pWetaSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Weta.png");
	m_pCatSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Cat.png");
	m_pGoatSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Goat.png");
	m_pBuzzyBeeSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\BuzzyBee.png");
	m_pAlienSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Alien.png");

	m_pMoreporkSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Morepork.png");
	m_pSeagullSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Seagull.png");
	m_pKeaSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Kea.png");
	m_pAirNZPlaneSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\AirNZPlane.png");
	m_pRocketSprite = SpriteManager::GetInstance().CreateSprite("assets\\enemies\\Rocket.png");
}


EnemyFactory&
EnemyFactory::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyFactory();
	}

	return *sm_pInstance;
}
void
EnemyFactory::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

//****************//

/*
Enemy*
EnemyFactory::CreateGroundPassiveEnemy()
{
	Enemy* newGroundPassiveEnemy = new GroundAggressiveEnemy;

	

	return newGroundPassiveEnemy;
}

Enemy* 
EnemyFactory::CreateGroundAggressiveEnemy()
{
	Enemy* newGroundAggressiveEnemy;

	//Need to check what level it is currently
	PlayState::Level currentLevel = PlayState::GetInstance()->GetCurrentLevel();

	switch (currentLevel)
	{
	case PlayState::Level::FOREST:
		newGroundAggressiveEnemy = new Weta();
		newGroundAggressiveEnemy->Initialise(m_pWetaSprite);
		break;
	case PlayState::Level::CITY:
		break;
	case PlayState::Level::CLOUD:
		break;
	case PlayState::Level::MOUNTAIN:
		break;
	case PlayState::Level::SPACE:
		break;
	}

	return newGroundAggressiveEnemy;
}

Enemy* 
EnemyFactory::CreateFlyingAggressiveEnemy()
{
	Enemy* newFlyingAggressiveEnemy;

	//Need to check what level it is currently
	PlayState::Level currentLevel = PlayState::GetInstance()->GetCurrentLevel();

	switch (currentLevel)
	{
	case PlayState::Level::FOREST:
		newFlyingAggressiveEnemy = new Kea();
		newFlyingAggressiveEnemy->Initialise(m_pKeaSprite);
		break;
	case PlayState::Level::CITY:
		break;
	case PlayState::Level::CLOUD:
		break;
	case PlayState::Level::MOUNTAIN:
		break;
	case PlayState::Level::SPACE:
		break;
	}

	return newFlyingAggressiveEnemy;
}
*/

Enemy*
EnemyFactory::CreateGroundPassiveEnemy()
{
	Enemy* newGroundPassiveEnemy = new GroundPassiveEnemy();
	newGroundPassiveEnemy->Initialise(m_pPossumSprite); //Give default sprite
	return newGroundPassiveEnemy;
}

Enemy*
EnemyFactory::CreateGroundAggressiveEnemy()
{
	Enemy* newGroundAggressiveEnemy = new GroundAggressiveEnemy();
	newGroundAggressiveEnemy->Initialise(m_pWetaSprite); //Give default sprite
	return newGroundAggressiveEnemy;
}

Enemy*
EnemyFactory::CreateFlyingAggressiveEnemy()
{
	Enemy* newFlyingAggressiveEnemy = new FlyingAggressiveEnemy();
	newFlyingAggressiveEnemy->Initialise(m_pMoreporkSprite); //Give default sprite
	return newFlyingAggressiveEnemy;
}

void
EnemyFactory::ProcessCurrentGroundPassiveEnemy(GroundPassiveEnemy* enemy)
{
	//Need to check what level it is currently
	PlayState::Level currentLevel = PlayState::GetInstance()->GetCurrentLevel();

	switch (currentLevel)
	{
	case PlayState::Level::FOREST:
		enemy->Initialise(m_pPossumSprite);
		break;
	case PlayState::Level::CITY:
		enemy->Initialise(m_pRatSprite);
		break;
	case PlayState::Level::MOUNTAIN:
		enemy->Initialise(m_pSheepSprite);
		break;
	case PlayState::Level::CLOUD:
		enemy->Initialise(m_pUnicornSprite);
		break;
	case PlayState::Level::SPACE:
		enemy->Initialise(m_pFleebSprite);
		break;
	default:
		enemy->Initialise(m_pPossumSprite);
		break;
	}
}

void 
EnemyFactory::ProcessCurrentGroundAggressiveEnemy(GroundAggressiveEnemy* enemy)
{
	//Need to check what level it is currently
	PlayState::Level currentLevel = PlayState::GetInstance()->GetCurrentLevel();

	switch (currentLevel)
	{
	case PlayState::Level::FOREST:
		enemy->Initialise(m_pWetaSprite);
		break;
	case PlayState::Level::CITY:
		enemy->Initialise(m_pCatSprite);
		break;
	case PlayState::Level::MOUNTAIN:
		enemy->Initialise(m_pGoatSprite);
		break;
	case PlayState::Level::CLOUD:
		enemy->Initialise(m_pBuzzyBeeSprite);
		break;
	case PlayState::Level::SPACE:
		enemy->Initialise(m_pAlienSprite);
		break;
	default:
		enemy->Initialise(m_pWetaSprite);
		break;
	}
}

void 
EnemyFactory::ProcessCurrentFlyingAggressiveEnemy(FlyingAggressiveEnemy* enemy)
{
	//Need to check what level it is currently
	PlayState::Level currentLevel = PlayState::GetInstance()->GetCurrentLevel();

	switch (currentLevel)
	{
	case PlayState::Level::FOREST:
		enemy->Initialise(m_pMoreporkSprite);
		break;
	case PlayState::Level::CITY:
		enemy->Initialise(m_pSeagullSprite);
		break;
	case PlayState::Level::MOUNTAIN:
		enemy->Initialise(m_pKeaSprite);
		break;
	case PlayState::Level::CLOUD:
		enemy->Initialise(m_pAirNZPlaneSprite);
		break;
	case PlayState::Level::SPACE:
		enemy->Initialise(m_pRocketSprite);
		break;
	default:
		enemy->Initialise(m_pMoreporkSprite);
		break;
	}
}