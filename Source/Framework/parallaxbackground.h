#ifndef __PARALLAXBACKGROUND_H__
#define __PARALLAXBACKGROUND_H__

// Superclass include:
#include "background.h"

// Forward Declarations:
class Sprite;
class BackBuffer;
class Entity;
class Background;

class ParallaxBackground : public Background
{
	//Member Methods:
public:
	ParallaxBackground();
	~ParallaxBackground();

	bool Initialise(Sprite* sprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	float GetCurrentPortionY();
	void ShiftPortionDown(float pixelChange);

protected:

private:
	ParallaxBackground(const ParallaxBackground& bg);
	ParallaxBackground& operator=(const ParallaxBackground& bg);

	//Member Data:
public:

protected:

private:

	//Portion data
	int m_screenW;
	int m_screenH;
	float m_portionX;
	float m_portionY;

};

#endif __PARALLAXBACKGROUND_H__
