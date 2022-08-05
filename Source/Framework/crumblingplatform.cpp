#include "crumblingplatform.h"


#include "backbuffer.h"
#include "colour.h"
#include "playstate.h"
#include "entity.h"
#include "player.h"
#include "soundmanager.h"
#include "logmanager.h"

#include <stdio.h>

#include "spritemanager.h"

CrumblingPlatform::CrumblingPlatform()
	: m_crumble(false)
	, m_soundEffectPlayed(false)
	, m_respawnCountdown(0.0f)
{
	m_dead = false;
}

CrumblingPlatform::~CrumblingPlatform()
{
}

bool CrumblingPlatform::Initialise(Vector2 position, int width, int height, float timeToBreak)
{
	m_relativePos = position;
	m_position = position;
	m_width = width;
	m_height = height;
	m_timeToBreak = timeToBreak;
	m_dead = false;

	if (width == 30)
	{
		m_pSprite = SpriteManager::CreateSpriteFromSheet("assets//PlatformSpriteSheet.png", 210, 0, width, 30);
	}
	else
	{
		m_pSprite = SpriteManager::CreateSpriteFromSheet("assets//PlatformSpriteSheet.png", 210, width - 30, width, 30);
	}
	
	return true;
}

bool CrumblingPlatform::Initialise(Sprite* sprite)
{
	//TODO: Implement sprite platform.
	return false;
}

void CrumblingPlatform::Process(float deltaTime)
{
	if (m_crumble)
	{
		//Reduce time to break
		m_timeToBreak -= deltaTime;
	}

	//If timeto break is less than 0
	if (m_timeToBreak < 0)
	{
		//Destroy platform
		SetDead(true);
		if (!m_soundEffectPlayed)
		{
			//Play crumble sound
			SoundManager::GetInstance().PlayCrumblePlatformSFX();
			m_soundEffectPlayed = true;
		}
	}

	//If platform is dead, start counting down for respawn
	if (IsDead())
	{
		//Debug Stub
		/*char buffer[100];
		sprintf_s(buffer, "Time to respawn is %f", m_timeToRespawn);
		LogManager::GetInstance().Log(buffer);*/
		//
		m_respawnCountdown += deltaTime;
		if (m_respawnCountdown > 10.0f)
		{
			//LogManager::GetInstance().Log("Spawning!");
			this->ResetPlatform();
			m_respawnCountdown -= 10.0f;
		}
	}
}

void CrumblingPlatform::Draw(BackBuffer& backBuffer)
{
	if (!IsDead())
	{
		if (m_pSprite != nullptr)
		{
			backBuffer.DrawFromSpriteSheet(*m_pSprite, m_position.GetXi(), m_position.GetYi());
		}
		else {
			backBuffer.SetDrawColour(Colour(142, 77, 0));
			backBuffer.DrawRectangle(m_position.GetXi(), m_position.GetYi(), m_position.GetXi() + m_width, m_position.GetYi() + m_height);
		}
	}
}

bool 
CrumblingPlatform::IsCollidingWith(Entity& e)
{
	return Platform::IsCollidingWith(e);
}

bool 
CrumblingPlatform::IsCollidingWith(int x, int y, int w, int h)
{
	if (IsCollidingWith(*PlayState::GetInstance()->GetPlayer()) && Platform::IsCollidingWith(x, y, w, h))
	{
		m_crumble = true;
	}

	return Platform::IsCollidingWith(x, y, w, h);
}

bool CrumblingPlatform::IsCrumbling()
{
	return m_crumble;
}

void CrumblingPlatform::SetCrumbling(bool crumble)
{
	m_crumble = crumble;
}

void CrumblingPlatform::ResetPosition(Vector2 sectionPosition)
{
	Platform::ResetPosition(sectionPosition);
	ResetPlatform();
}

void 
CrumblingPlatform::ResetPlatform()
{
	SetCrumbling(false);
	SetDead(false);
	m_timeToBreak = 5;
}

void CrumblingPlatform::SetDead(bool dead)
{
	if (dead == true)
	{
		SetCrumbling(false);
	}
	m_dead = dead;
}