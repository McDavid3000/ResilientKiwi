#ifndef __ENEMYFACTORY_H__
#define __ENEMYFACTORY_H__

// Forward Declarations:
class Enemy;
class GroundPassiveEnemy;
class GroundAggressiveEnemy;
class FlyingAggressiveEnemy;

class Sprite;

//Singleton class to create enemies based on game conditions - called primarily from SectionManager
class EnemyFactory
{
	// --- Member methods ---
public:
	static EnemyFactory& GetInstance();
	static void DestroyInstance();

	Enemy* CreateGroundPassiveEnemy();
	Enemy* CreateGroundAggressiveEnemy();
	Enemy* CreateFlyingAggressiveEnemy();

	void ProcessCurrentGroundPassiveEnemy(GroundPassiveEnemy * enemy);
	void ProcessCurrentGroundAggressiveEnemy(GroundAggressiveEnemy * enemy);
	void ProcessCurrentFlyingAggressiveEnemy(FlyingAggressiveEnemy * enemy);



protected:

private:
	EnemyFactory();


	// --- Member data ---
public:

protected:
	static EnemyFactory* sm_pInstance;

private:
	//Ground Passive Enemies
	Sprite* m_pPossumSprite;
	Sprite* m_pRatSprite;
	Sprite* m_pSheepSprite;
	Sprite* m_pUnicornSprite;
	Sprite* m_pFleebSprite;

	//Ground Aggressive Enemies
	Sprite* m_pWetaSprite;
	Sprite* m_pCatSprite;
	Sprite* m_pGoatSprite;
	Sprite* m_pBuzzyBeeSprite;
	Sprite* m_pAlienSprite;

	//Flying Aggressive Enemies
	Sprite* m_pMoreporkSprite;
	Sprite* m_pSeagullSprite;
	Sprite* m_pKeaSprite;
	Sprite* m_pAirNZPlaneSprite;
	Sprite* m_pRocketSprite;
};

#endif //__SPRITEMANAGER_H__