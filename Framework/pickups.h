//Superclass include
#include "entity.h"
#include "sparkleemitter.h"

#include <list>

#ifndef __PICKUPS_H__
#define __PICKUPS_H__

// Forward Declarations:
class BackBuffer;
class Sprite;
class Vector2;
class Player;
class Platform;

class PickUps : public Entity
{
	// --- Member methods ---
public:
	PickUps();
	void Process(float deltaTime);
	void Draw(BackBuffer & backBuffer);
	~PickUps();

	//check this pickup is colliding with player
	bool CheckPlayerCollision(Player* player);
	virtual void ActivatePickUp(Player* player) = 0;

	void SetRelativePosition(Vector2 position);
	virtual void UpdatePosition(Vector2 position);
	virtual void ResetPosition(Vector2 sectionPosition);

	void SetSectionPlatforms(std::list<Platform*> sectionPlatforms);

protected:


private:

	// --- Member data ---
public:

protected:
	//Position data to be moved down with the environment
	Vector2 m_relativePos;
	std::list<Platform*> m_pSectionPlatforms;
	SparkleEmitter m_sparkleEmitter;


private:

};

#endif __PICKUPS_H__