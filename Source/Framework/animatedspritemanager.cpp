#include "animatedspritemanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "spritemanager.h"
#include "player.h"

AnimatedSpriteManager::AnimatedSpriteManager() 
{
}

AnimatedSpriteManager::~AnimatedSpriteManager()
{
	delete m_pStandingLeftSprite;
	m_pStandingLeftSprite = 0;
	
	delete m_pStandingRightSprite;
	m_pStandingRightSprite = 0;

	delete m_pRunningLeftSprite;
	m_pRunningLeftSprite = 0;

	delete m_pRunningRightSprite;
	m_pRunningRightSprite = 0;

	delete m_pJumpingLeftSprite;
	m_pRunningLeftSprite = 0;

	delete m_pJumpingRightSprite;
	m_pRunningRightSprite = 0;
}

void AnimatedSpriteManager::Initialise()
{
	//Initialise Kiwi Sprites
	//Standing

	Sprite* PlayerSpriteSheet = SpriteManager::GetInstance().CreateSprite("assets\\PlayerSpriteSheetV2.png");
	
	m_pStandingLeftSprite = new AnimatedSprite();
	m_pStandingRightSprite = new AnimatedSprite();

	m_pStandingLeftSprite->SetTotalFrames(7);
	m_pStandingLeftSprite->SetFrameSpeed(0.1f);
	m_pStandingLeftSprite->SetFrameWidth(100);
	m_pStandingLeftSprite->SetFrameHeight(100);
	m_pStandingLeftSprite->Initialise(*PlayerSpriteSheet->GetTexture(), 0);

	m_pStandingRightSprite->SetTotalFrames(7);
	m_pStandingRightSprite->SetFrameSpeed(0.1f);
	m_pStandingRightSprite->SetFrameWidth(100);
	m_pStandingRightSprite->SetFrameHeight(100);
	m_pStandingRightSprite->Initialise(*PlayerSpriteSheet->GetTexture(), 100);
	
	//Jumping
	m_pJumpingLeftSprite = new AnimatedSprite();
	m_pJumpingRightSprite = new AnimatedSprite();

	m_pJumpingLeftSprite->SetTotalFrames(4);
	m_pJumpingLeftSprite->SetFrameSpeed(0.2f);
	m_pJumpingLeftSprite->SetFrameWidth(100);
	m_pJumpingLeftSprite->SetFrameHeight(100);
	m_pJumpingLeftSprite->Initialise(*PlayerSpriteSheet->GetTexture(), 200);

	m_pJumpingRightSprite->SetTotalFrames(4);
	m_pJumpingRightSprite->SetFrameSpeed(0.2f);
	m_pJumpingRightSprite->SetFrameWidth(100);
	m_pJumpingRightSprite->SetFrameHeight(100);
	m_pJumpingRightSprite->Initialise(*PlayerSpriteSheet->GetTexture(), 300);

	//Running
	m_pRunningLeftSprite = new AnimatedSprite();
	m_pRunningRightSprite = new AnimatedSprite();

	m_pRunningLeftSprite->SetTotalFrames(4);
	m_pRunningLeftSprite->SetFrameSpeed(0.2f);
	m_pRunningLeftSprite->SetFrameWidth(100);
	m_pRunningLeftSprite->SetFrameHeight(100);
	m_pRunningLeftSprite->Initialise(*PlayerSpriteSheet->GetTexture(), 400);

	m_pRunningRightSprite->SetTotalFrames(4);
	m_pRunningRightSprite->SetFrameSpeed(0.2f);
	m_pRunningRightSprite->SetFrameWidth(100);
	m_pRunningRightSprite->SetFrameHeight(100);
	m_pRunningRightSprite->Initialise(*PlayerSpriteSheet->GetTexture(), 500);

}

AnimatedSprite * AnimatedSpriteManager::GetStandingRight()
{
	return m_pStandingRightSprite;
}

AnimatedSprite * AnimatedSpriteManager::GetStandingLeft()
{
	return m_pStandingLeftSprite;
}

AnimatedSprite * AnimatedSpriteManager::GetRunningRight()
{
	return m_pRunningRightSprite;
}

AnimatedSprite * AnimatedSpriteManager::GetRunningLeft()
{
	return m_pRunningLeftSprite;
}

AnimatedSprite * AnimatedSpriteManager::GetJumpingRight()
{
	return m_pJumpingRightSprite;
}

AnimatedSprite * AnimatedSpriteManager::GetJumpingLeft()
{
	return m_pJumpingLeftSprite;
}
