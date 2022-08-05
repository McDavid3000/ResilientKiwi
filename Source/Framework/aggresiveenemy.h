//Superclass include
#include "enemy.h"

#ifndef __AGGRESSIVEENEMY_H__
#define __AGGRESSIVEENEMY_H__

// Forward Declarations:


class AggressiveEnemy : public Enemy
{
	//Member methods
public:
	AggressiveEnemy();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetAIState(AIState state);

	void ProcessAI(float deltaTime);

	//AI classes/states
	enum AIState {
		PACING,
		ATTACKING
	};
	enum Direction {
		LEFT,
		RIGHT
	};


protected:

private:


	//Member data
public:

protected:


private:

};

#endif //__AGGRESSIVEENEMY_H__