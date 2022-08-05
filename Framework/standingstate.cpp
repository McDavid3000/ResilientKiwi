#include "standingstate.h"
#include "jumpingstate.h"
#include "walkingstate.h"
#include "player.h"
#include "playerstates.h"
#include "backbuffer.h"
#include "spritemanager.h"
#include "animatedsprite.h"
#include "animatedspritemanager.h"
#include "soundmanager.h"
#include "playstate.h"

StandingState::StandingState()
{
}

StandingState::~StandingState()
{
}

void StandingState::Initialise(Player * player)
{
	m_pPlayer = player;

	m_pLeftSprite = m_pAnimatedSpriteManager->GetStandingLeft();
	m_pRightSprite = m_pAnimatedSpriteManager->GetStandingRight();

	m_pLeftSprite->SetX(m_pPlayer->GetPosition().GetXi());
	m_pLeftSprite->SetY(m_pPlayer->GetPosition().GetYi());

	m_pRightSprite->SetX(m_pPlayer->GetPosition().GetXi());
	m_pRightSprite->SetY(m_pPlayer->GetPosition().GetYi());
}

void
StandingState::Process(float deltaTime)
{
	PlayerStates::Process(deltaTime);

	PlayerStates::CheckPlayerPlatformCollision();
}

void 
StandingState::Draw(BackBuffer & backBuffer)
{
	if (PlayState::GetInstance()->GetDrawDebug())
	{
		char buffer[128];
		backBuffer.SetTextColour(Colour(255, 0, 0));
		sprintf(buffer, "State: STANDING");
		backBuffer.DrawText(0, 150, buffer);
	}
}

void 
StandingState::HandleInput(SDL_Keycode key)
{
	PlayerStates::HandleInput(key);

	if (key == SDLK_a || key == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
	{
		ChangePlayerState(m_pPlayer->GetStateManager().GetWalkingState());
	}
	else if (key == SDLK_d || key == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		ChangePlayerState(m_pPlayer->GetStateManager().GetWalkingState());
	}
	else if (key == SDLK_SPACE || key == SDL_CONTROLLER_BUTTON_A)
	{
		m_pPlayer->Jump();
		SoundManager::GetInstance().PlayJumpSFX();
		ChangePlayerState(m_pPlayer->GetStateManager().GetJumpingState());
	}
}


