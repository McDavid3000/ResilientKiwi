#pragma once
#include "platform.h"
class MovingPlatform : public Platform
{
public:
	/*Determines the direction the platform is moving*/
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	MovingPlatform();
	~MovingPlatform();
	
	bool Initialise(Vector2 positionOne, Vector2 positionTwo, int width, int height);
	bool Initialise(Sprite* sprite) override;
	void Process(float deltaTime) override;
	void Draw(BackBuffer& backBuffer) override;
	void ResetPosition(Vector2 sectionPosition);
	/*Adjusts the platform position, and travel ranges by the given position*/
	void UpdatePosition(Vector2 position) override;
	bool IsCollidingWith(Entity& e) override;
	void SetDirection(Direction direction);

protected:
private:

public:
protected:
	Vector2 m_firstPosition;
	Vector2 m_secondPosition;
	
	Direction m_currentDirection;
private:
};

