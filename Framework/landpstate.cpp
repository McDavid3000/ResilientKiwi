#include "landpstate.h"
#include "fallingstate.h"
#include "player.h"
#include "backbuffer.h"
#include "animatedsprite.h"
#include "spritemanager.h"
#include "animatedspritemanager.h"
#include "playstate.h"

LandPState::LandPState()
{
}

LandPState::~LandPState()
{
}

void 
LandPState::Initialise(Player * player)
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
LandPState::Process(float deltaTime)
{
	PlayerStates::Process(deltaTime);

	if (m_pPlayer->GetVerticalVelocity() > 0)
	{
		ChangePlayerState(m_pPlayer->GetStateManager().GetFallingState());
	}
}

void 
LandPState::Draw(BackBuffer & backBuffer)
{
	if (PlayState::GetInstance()->GetDrawDebug())
	{
		char buffer[128];
		backBuffer.SetTextColour(Colour(255, 0, 0));
		sprintf(buffer, "State: L AND P");
		backBuffer.DrawText(0, 150, buffer);
	}
}

void 
LandPState::HandleInput(SDL_Keycode key)
{
	PlayerStates::HandleInput(key);
}

