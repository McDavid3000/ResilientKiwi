// This include:
#include "parallaxbackground.h"

// Local includes:
#include "entity.h"
#include "sprite.h"
#include "backbuffer.h"

// Library Includes
#include <cassert>


// Forward Declarations:


ParallaxBackground::ParallaxBackground()
: m_screenW(480)
, m_screenH(854)
{

}

ParallaxBackground::~ParallaxBackground()
{

}


bool 
ParallaxBackground::Initialise(Sprite* sprite)
{
	//Set sprite
	assert(sprite);
	m_pSprite = sprite;

	//Set initial portion data
	m_portionX = 0;
	m_portionY = float(m_pSprite->GetHeight() - m_screenH);

	return (true);
}

void 
ParallaxBackground::Process(float deltaTime)
{

}

void
ParallaxBackground::Draw(BackBuffer& backBuffer)
{
	backBuffer.DrawSpritePortion(*m_pSprite, int(m_portionX), int(m_portionY), m_screenW, m_screenH);
}

float 
ParallaxBackground::GetCurrentPortionY()
{
	return m_portionY;
}

void 
ParallaxBackground::ShiftPortionDown(float pixelChange)
{
	m_portionY -= pixelChange;
}