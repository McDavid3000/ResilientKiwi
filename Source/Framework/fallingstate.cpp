#include "fallingstate.h"
#include "standingstate.h"
#include "walkingstate.h"
#include "player.h"
#include "playstate.h"
#include "backbuffer.h"
#include "spritemanager.h"
#include "animatedsprite.h"
#include "animatedspritemanager.h"

FallingState::FallingState()
{
}

FallingState::~FallingState()
{
}

void
FallingState::Initialise(Player * player)
{
	m_pPlayer = player;

	m_pLeftSprite = m_pAnimatedSpriteManager->GetJumpingLeft();
	m_pRightSprite = m_pAnimatedSpriteManager->GetJumpingRight();

	m_pLeftSprite->SetX(m_pPlayer->GetPosition().GetXi());
	m_pLeftSprite->SetY(m_pPlayer->GetPosition().GetYi());

	m_pRightSprite->SetX(m_pPlayer->GetPosition().GetXi());
	m_pRightSprite->SetY(m_pPlayer->GetPosition().GetYi());
}

void
FallingState::Process(float deltaTime)
{
	PlayerStates::Process(deltaTime);

	PlayerStates::CheckPlayerPlatformCollision();

	if (m_pPlayer->GetVerticalVelocity() == 0 && m_pPlayer->GetHorizontalVelocity() == 0)
	{
		//spawn dust particles 
		m_pPlayer->GetDustEmitter().SetPosition(Vector2(m_pPlayer->GetCentrePosition().x, m_pPlayer->GetCentrePosition().y + (m_pPlayer->GetHeight() / 2)));
 		m_pPlayer->GetDustEmitter().SpawnParticles();
		
		//Set L and P  to false for enemy collision detection
		m_pPlayer->SetLandP(false);

		ChangePlayerState(m_pPlayer->GetStateManager().GetStandingState());

	}
	else if (m_pPlayer->GetVerticalVelocity() == 0 && m_pPlayer->GetHorizontalVelocity() != 0)
	{
		//spawn dust particles 
		m_pPlayer->GetDustEmitter().SetPosition(Vector2(m_pPlayer->GetCentrePosition().x, m_pPlayer->GetCentrePosition().y + (m_pPlayer->GetHeight() / 2)));
		m_pPlayer->GetDustEmitter().SpawnParticles();

		//Set L and P  to false for enemy collision detection
		m_pPlayer->SetLandP(false);

		ChangePlayerState(m_pPlayer->GetStateManager().GetWalkingState());
	}
}


void
FallingState::Draw(BackBuffer & backBuffer)
{
	if (PlayState::GetInstance()->GetDrawDebug())
	{
		char buffer[128];
		backBuffer.SetTextColour(Colour(255, 0, 0));
		sprintf(buffer, "State: FALLING");
		backBuffer.DrawText(0, 150, buffer);
	}
}

void
FallingState::HandleInput(SDL_Keycode key)
{
	PlayerStates::HandleInput(key);
}


