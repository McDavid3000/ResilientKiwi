//Superclass include
#include "entity.h"

#ifndef __LASERBEAM_H__
#define __LASERBEAM_H__

//Forward declarations
class Entity;
class Enemy;
class Player;

//Local includes
#include <list>

class LaserBeam : public Entity
{
	//Member methods
public:
	LaserBeam();

	enum Direction {
		LEFT,
		RIGHT,
		UP
	};

	bool Initialise(Sprite* sprite, Player* player, LaserBeam::Direction direction);
	void Process(float deltaTime, std::list<Enemy*> enemyList);
	void Draw(BackBuffer& backBuffer);

	bool IsCollidingWith(Entity& e);

protected:
private:

	//Member data
public:
protected:
private:
	float m_laserSpeed;
	int m_laserDamage;
	int m_laserRotationValue;

	//Reference to player
	Player* m_pPlayer;

};

#endif // __LASERBEAM_H__