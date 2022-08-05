//Superclass include
#include "entity.h"

#ifndef __ENEMY_H__
#define __ENEMY_H__

// Forward Declarations:
class Platform;

#include <list>

class Enemy : public Entity
{
	//Member methods
public:
	Enemy();
	~Enemy();

	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);

	virtual void UpdatePosition(Vector2 position);
	virtual void ResetPosition(Vector2 sectionPosition);
	void SetRelativePosition(Vector2 position);
	Vector2 GetRelativePosition();

	virtual bool IsCollidingWith(Entity& e);
	virtual bool IsCollidingWith(int x, int y, int w, int h);
	virtual bool IsCircleCollidingWith(Entity& e);

	int GetMovementSpeed();

	void SetSectionPlatforms(std::list<Platform*> sectionPlatforms);

	void DeductHitpoints(int hitpoints);

	//AI methods
	virtual void ProcessAI(float deltaTime);

	enum AIState {
		PACING,
		ATTACKING
	};

	void SetAIState(AIState state);

	enum EnemySpeed {
		SLOW,
		MEDIUM,
		FAST
	};


protected:

private:


	//Member data
public:

protected:
	//Movement speed data 
	EnemySpeed m_movementSpeedCategory;

	//Health data
	int m_hitpoints;

	AIState m_pCurrentAIState;

	//Position data to be moved down with the environment
	Vector2 m_relativePos;

	//Reference to all the platforms in the section
	std::list<Platform*> m_pSectionPlatforms;

private:
	int m_movementSpeed; //Category can be set, but this number only to be altered automatically based on cat

};

#endif //__ENEMY_H__