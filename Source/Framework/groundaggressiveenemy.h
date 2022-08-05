//Superclass include
#include "aggresiveenemy.h"

#ifndef __GROUNDAGGRESSIVEENEMY_H__
#define __GROUNDAGGRESSIVEENEMY_H__

// Forward Declarations:
class Platform;

class GroundAggressiveEnemy : public AggressiveEnemy
{
	//Member methods
public:
	GroundAggressiveEnemy();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void ProcessAI(float deltaTime);

protected:

private:


	//Member data
public:

protected:


private:
	AIState m_currentAIState;
	Direction m_paceDirection;

	//Reference to the platform the enemy is standing on
	Platform* m_pStandingPlatform;
};

#endif //__GROUNDAGGRESSIVEENEMY_H__