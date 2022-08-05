// COMP710 GP 2D Framework 2020
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;

#include "vector2.h"

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	//void DrawAnimatedSprite(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	Vector2 GetPosition() const;
	void SetPosition(Vector2 position);
	void SetPositionX(float x);
	void SetPositionY(float y);

	Vector2 GetVelocity() const;
	void SetVelocity(Vector2 velocity);
	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	void SetAlpha(unsigned char alpha);
	unsigned char GetAlpha();

	int GetWidth();
	int	GetHeight();

	Sprite* GetSprite();

	Vector2 GetCentrePosition();

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

	const char* m_pSpriteFileName;

	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_centerPosition;

	bool m_dead;

private:

};

#endif //__ENTITY_H__
