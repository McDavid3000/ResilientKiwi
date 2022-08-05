// This include:
#include "pickupfactory.h"

// Local includes:
#include "playstate.h"
#include "spritemanager.h"
#include "sprite.h"

#include "kiwicoin.h"
#include "landppowerup.h"
#include "hivispowerup.h"
#include "gumbootpowerup.h"

// Library includes:

// Static members 
PickUpFactory* PickUpFactory::sm_pInstance = 0;

PickUpFactory::PickUpFactory()
{
	//Create all the pickup sprites
	m_pGumbootsSprite = SpriteManager::GetInstance().CreateSprite("assets\\gumboots.png");
	m_pHiVisSprite = SpriteManager::GetInstance().CreateSprite("assets\\hivispowerup.png");
	m_pKiwiCoinSprite = SpriteManager::GetInstance().CreateSprite("assets\\kiwicoin.png");
	m_pLandPSprite = SpriteManager::GetInstance().CreateSprite("assets\\landp.png");
}

PickUpFactory & 
PickUpFactory::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new PickUpFactory();
	}

	return *sm_pInstance;
}

void
PickUpFactory::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

PickUps * 
PickUpFactory::CreateKiwiCoin()
{
	KiwiCoin* newKiwiCoin;

	newKiwiCoin = new KiwiCoin();
	newKiwiCoin->Initialise(m_pKiwiCoinSprite);

	return newKiwiCoin;
}

PickUps * 
PickUpFactory::CreateLandPPowerUp()
{
	LandPPowerUp* newLandP;

	newLandP = new LandPPowerUp();
	newLandP->Initialise(m_pLandPSprite);

	return newLandP;
}

PickUps * 
PickUpFactory::CreateGumbootsPowerUp()
{
	GumbootPowerUp* newGumboots;

	newGumboots = new GumbootPowerUp();
	newGumboots->Initialise(m_pGumbootsSprite);

	return newGumboots;
}

PickUps * 
PickUpFactory::CreateHiVisPowerUp()
{
	HiVisPowerUp* newHiVis;

	newHiVis = new HiVisPowerUp();
	newHiVis->Initialise(m_pHiVisSprite);

	return newHiVis;
}