//Superclass include
#include "aggresiveenemy.h"

#ifndef __FLYINGAGGRESSIVEENEMY_H__
#define __FLYINGAGGRESSIVEENEMY_H__

// Forward Declarations:
class Platform;

class FlyingAggressiveEnemy : public AggressiveEnemy
{
	//Member methods
public:
	FlyingAggressiveEnemy();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void ProcessAI(float deltaTime);

protected:

private:


	//Member data
public:

protected:


private:
	Direction m_paceDirection;

	float m_prevPos;
};

#endif //__FLYINGAGGRESSIVEENEMY_H__