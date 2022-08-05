//Superclass include
#include "entity.h"

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

// Forward Declarations:
class Sprite;

class Platform : public Entity
{
public:
	Platform();
	~Platform();

	/*Create platform with a width and height*/
	virtual bool Initialise(Vector2 position, int width, int height);
	virtual bool Initialise(Sprite* sprite);
	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);
	/*Adjusts the platform position by the given position*/
	virtual void UpdatePosition(Vector2 position);
	virtual void ResetPosition(Vector2 sectionPosition);
	void SetRelativePosition(Vector2 position);
	Vector2 GetRelativePosition();
	virtual bool IsCollidingWith(Entity& e);
	virtual bool IsCollidingWith(int x, int y, int w, int h); //Rectangle bound checking

	virtual void ResetPlatform();

	int GetWidth();
	int GetHeight();
	
protected:
private:

public:
protected:
	int m_width;
	int m_height;

	Vector2 m_relativePos;

	//Platform sprites TODO: For sprite sheet
	// Sprite* m_pStartSprite;
	// Sprite* m_middleSprite;
	// Sprite* m_pEndSprite;
private:
};

#endif //__PLATFORM_H__