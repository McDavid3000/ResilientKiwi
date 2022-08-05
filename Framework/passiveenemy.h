//Superclass include
#include "enemy.h"

#ifndef __PASSIVEENEMY_H__
#define __PASSIVEENEMY_H__

// Forward Declarations:


class PassiveEnemy : public Enemy
{
	//Member methods
public:
	PassiveEnemy();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);


protected:

private:


	//Member data
public:

protected:


private:

};

#endif //__PASSIVEENEMY_H__