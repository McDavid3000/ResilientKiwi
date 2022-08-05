//Superclass include
#include "passiveenemy.h"

#ifndef __GROUNDPASSIVEENEMY_H__
#define __GROUNDPASSIVEENEMY_H__

// Forward Declarations:
class Platform;

class GroundPassiveEnemy : public PassiveEnemy
{
	//Member methods
public:
	GroundPassiveEnemy();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	//AI classes/states
	enum Direction {
		LEFT,
		RIGHT
	};

	void ProcessAI(float deltaTime);

protected:

private:


	//Member data
public:

protected:


private:
	Direction m_paceDirection;

	//Reference to the platform the enemy is standing on
	Platform* m_pStandingPlatform;
};

#endif //__GROUNDPASSIVEENEMY_H__