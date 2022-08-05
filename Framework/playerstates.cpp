//This include
#include "playerstates.h"

//Local includes
#include "playstate.h"
#include "player.h"
#include "animatedsprite.h"
#include "animatedspritemanager.h"
#include "spritemanager.h"
#include "laserbeam.h"
#include "playstate.h"
#include "enemy.h"
#include "section.h"

PlayerStates::PlayerStates()
{
	m_pAnimatedSpriteManager = SpriteManager::GetInstance().GetAnimatedSpriteManager();
}

PlayerStates::~PlayerStates()
{
}

void 
PlayerStates::ChangePlayerState(PlayerStates * state)
{
	m_pPlayer->ChangePlayerState(state);
}

void 
PlayerStates::Process(float deltaTime)
{
	m_pPlayer->ApplyGravity();
	m_pPlayer->UpdatePosition(deltaTime);
	PerformBoundChecking();

	if (m_pPlayer->GetDirection() == Player::Direction::RIGHT)
	{
		m_pPlayer->SetCurrentSprite(m_pRightSprite);
	}
	else if (m_pPlayer->GetDirection() == Player::Direction::LEFT)
	{
		m_pPlayer->SetCurrentSprite(m_pLeftSprite);
	}
}

void 
PlayerStates::Draw(BackBuffer& backBuffer)
{
}

void
PlayerStates::HandleInput(SDL_Keycode key) 
{
	//Movement 
	if (key == SDLK_a || key == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
	{
		m_pPlayer->MoveLeft();
		m_pPlayer->SetDirection(Player::Direction::LEFT);
	}
	if (key == SDLK_d || key == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		m_pPlayer->MoveRight();
		m_pPlayer->SetDirection(Player::Direction::RIGHT);
	}
}

void
PlayerStates::CheckPlayerPlatformCollision()
{
	//If player is currently falling, and colliding with platform, stop player
	for (auto m_section : PlayState::GetInstance()->m_pSectionManager->m_activeSections)
	{
		for (auto m_platform : m_section->GetPlatforms())
		{
			// Getting bounds of player feet for platform collision
			int feetOffset = 30;
			int feetX = m_pPlayer->GetPosition().GetXi() + feetOffset;
			int feetY = m_pPlayer->GetPosition().GetYi() + ((m_pPlayer->GetHeight() / 8) * 7); //Bottom 1/8th of the sprite
			int feetW = m_pPlayer->GetWidth() - (feetOffset * 2);
			int feetH = m_pPlayer->GetHeight() - ((m_pPlayer->GetHeight() / 8) * 7);

			if (m_platform->IsCollidingWith(feetX, feetY, feetW, feetH))	//Collision with player feet
			{
				//	m_pPlayer->SetLanded(true);
				m_pPlayer->SetPositionY(m_platform->GetPosition().y - m_pPlayer->GetHeight());
				m_pPlayer->SetVerticalVelocity(0);

				if (m_platform->GetHorizontalVelocity() > 0)
				{
					if (m_pPlayer->GetVelocity().x <= 75 && m_pPlayer->GetVelocity().x >= -75)
					{
						m_pPlayer->SetHorizontalVelocity(m_platform->GetHorizontalVelocity());
					}
				}
				else if (m_platform->GetHorizontalVelocity() < 0)
				{
					if (m_pPlayer->GetVelocity().x >= -75 && m_pPlayer->GetVelocity().x <= 75)
					{
						m_pPlayer->SetHorizontalVelocity(m_platform->GetHorizontalVelocity());
					}
				}
			}
		}
	}
}

void
PlayerStates::PerformBoundChecking()
{
	float screenWidth = 480.0f;

	//Check if player is walking left
	//If player moves beyond left side of screen, place player on the right side of screen with a little offset
	if (m_pPlayer->GetDirection() == Player::Direction::LEFT)
	{
		if ((m_pPlayer->GetPosition().GetXi() + 60.0f) < 0)
		{
			//Shows half of the kiwi to create smooth transition effect
			m_pPlayer->SetPositionX(screenWidth - 20.0f);
		}
	}

	//Check if player is walking right
	//If player moves beyond left side of screen, place player on the left side of screen with a little offset
	if (m_pPlayer->GetDirection() == Player::Direction::RIGHT)
	{
		if (m_pPlayer->GetPosition().GetXi() + 30 > screenWidth)
		{
			//Shows half of the kiwi to create smooth transition effect
			m_pPlayer->SetPositionX(0.0f - (m_pPlayer->GetWidth() / 4) * 3.0f);
		}
	}
}
