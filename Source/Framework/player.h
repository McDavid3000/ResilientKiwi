//Superclass include
#include "entity.h"
#include "playerstates.h"
#include "statemanager.h"
#include "dustparticleemitter.h"

#include <SDL.h>
#include <vector>
#include <list>

#ifndef __PLAYER_H__
#define __PLAYER_H__

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;
class Vector2;
class PlayerStates;
class LaserBeam;
class PickUps;

class Player : public Entity
{
	// --- Member methods ---
public:

	//Direction kiwi is facing regardless of playerstate
	enum Direction
	{
		RIGHT,
		LEFT
	};

	Player();
	~Player();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void DrawPlayerDebugText(BackBuffer& backBuffer);

	//State machine related methods
	void HandleInput(SDL_Keycode key);
	bool CheckOnScreen();
	void ChangePlayerState(PlayerStates* state);
	StateManager& GetStateManager();

	//Gettter and setter for current animatedsprite method
	AnimatedSprite* GetCurrentSprite();
	void SetCurrentSprite(AnimatedSprite* currentSprite);

	void UpdatePosition(float deltaTime);
	float GetGravity();
	void ApplyGravity();

	//Movement methods
	void MoveLeft();
	void MoveRight();
	void Jump();
	//void SetLanded(bool isLanded);
	//bool isLanded();

	Direction GetDirection();
	void SetDirection(Direction direction);

	//Pickup related methods
	void ProcessPowerUps(float deltaTime);

	void SetGumboots(bool hasGumboots);
	void SetHiVis(bool hasHiVis);
	bool hasHiVis();
	void SetLandP(bool hasLandP);
	bool hasLandP();

	int GetCoins();
	void SetCoins(int coins);
	
	DustParticleEmitter& GetDustEmitter();

protected:

private:


	// --- Member data ---
public:

protected:


private:
	Vector2 m_startingPos;

	DustParticleEmitter m_dustEmitter;

	// Movement 
	float m_movementSpeed;
	float m_jumpPower;
	float m_gravity;
	bool m_isLanded;

	// coin counter
	int m_coinsCounter;

	// Gumboots powerup
	bool m_hasGumboots;
	float m_gumbootsTimer;
	float const MAX_GUMBOOTS_DURATION;
	// HiVis Powerup
	bool m_hasHiVis;
	float m_hiVisTimer;
	float const MAX_HIVIS_DURATION;
	// L and P Powerup
	bool m_hasLandP;
	//float m_landPTimer;
	//float const MAX_LANDP_DURATION;

	Direction m_currentDirection;

	//Player state
	StateManager m_stateManager;//Vector of playerstates
	std::vector<PlayerStates*> m_vecPlayerStates;

	//Current animated sprite gets set by different player states
	//TODO: Players current animated sprite needs to be set into some animation
	AnimatedSprite* m_pCurrentSprite;
	Sprite* m_pInvincibilityCircle;

	//Laserbeams
	std::list<LaserBeam*> m_pLaserBeams;
	Sprite* m_pLaserBeamSprite;

	//Manual Powerups for debug
	std::list<PickUps*> m_pPowerUps;
};

#endif //__PLAYER_H__