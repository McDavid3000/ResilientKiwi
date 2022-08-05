#include "walkingstate.h"
#include "jumpingstate.h"
#include "standingstate.h"
#include "fallingstate.h"
#include "player.h"
#include "backbuffer.h"
#include "animatedsprite.h"
#include "spritemanager.h"
#include "animatedspritemanager.h"
#include "soundmanager.h"
#include "playstate.h"

WalkingState::WalkingState()
{
}

WalkingState::~WalkingState()
{
}

void 
WalkingState::Initialise(Player * player)
{
	m_pPlayer = player;

	m_pLeftSprite = m_pAnimatedSpriteManager->GetRunningLeft();
	m_pRightSprite = m_pAnimatedSpriteManager->GetRunningRight();

	//Running Left Sprite
	m_pLeftSprite->SetX(m_pPlayer->GetPosition().GetXi());
	m_pLeftSprite->SetY(m_pPlayer->GetPosition().GetYi());

	//Running Right Sprite
	m_pRightSprite->SetX(m_pPlayer->GetPosition().GetXi());
	m_pRightSprite->SetY(m_pPlayer->GetPosition().GetYi());
}

void 
WalkingState::Process(float deltaTime)
{
	PlayerStates::Process(deltaTime);

	PlayerStates::CheckPlayerPlatformCollision();

	if (m_pPlayer->GetVelocity().GetXi() <= 75 && m_pPlayer->GetVelocity().GetXi() >= -75 && m_pPlayer->GetVelocity().GetYi() == 0)
	{
		ChangePlayerState(m_pPlayer->GetStateManager().GetStandingState());
	}

	if (m_pPlayer->GetVelocity().GetYi() != 0)
	{
		ChangePlayerState(m_pPlayer->GetStateManager().GetFallingState());
	}
}

void 
WalkingState::Draw(BackBuffer & backBuffer)
{
	if (PlayState::GetInstance()->GetDrawDebug())
	{
		char buffer[128];
		backBuffer.SetTextColour(Colour(255, 0, 0));
		sprintf(buffer, "State: WALKING");
		backBuffer.DrawText(0, 150, buffer);
	}
}

void 
WalkingState::HandleInput(SDL_Keycode key)
{
	PlayerStates::HandleInput(key);

	if (key == SDLK_SPACE || key == SDL_CONTROLLER_BUTTON_A)
	{
		m_pPlayer->Jump();
		SoundManager::GetInstance().PlayJumpSFX();
		ChangePlayerState(m_pPlayer->GetStateManager().GetJumpingState());
	}
}

