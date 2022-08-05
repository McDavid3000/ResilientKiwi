#ifndef __PICKUPFACTORY_H__
#define __PICKUPFACTORY_H__

// Forward Declarations:
class PickUps;
class Sprite;

//Singleton class to create game pickups based on game conditions - called primarily from SectionManager
class PickUpFactory
{
	// --- Member methods ---
public:
	static PickUpFactory& GetInstance();
	static void DestroyInstance();

	PickUps* CreateKiwiCoin();
	PickUps* CreateLandPPowerUp();
	PickUps* CreateGumbootsPowerUp();
	PickUps* CreateHiVisPowerUp();

protected:

private:
	PickUpFactory();


	// --- Member data ---
public:

protected:
	static PickUpFactory* sm_pInstance;

private:
	//Kiwicoin sprite
	Sprite* m_pKiwiCoinSprite;

	//Gumboot sprite
	Sprite* m_pGumbootsSprite;

	//HiVis sprite
	Sprite* m_pHiVisSprite;

	//L&P sprite
	Sprite* m_pLandPSprite;

};

#endif //__PICKUPFACTORY_H__