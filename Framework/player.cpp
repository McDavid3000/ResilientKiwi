// This include:
#include "player.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "spritemanager.h"
#include "vector2.h"
#include "logmanager.h"
#include "backbuffer.h"
#include "playerstates.h"
#include "standingstate.h"
#include "fallingstate.h"
#include "landpstate.h"
#include "laserbeam.h"
#include "playstate.h"
#include "soundmanager.h"
#include "hivispowerup.h"


// Library includes
#include <list>

Player::Player()
: m_currentDirection(RIGHT)
, m_movementSpeed(150)
, m_gravity(5)
, m_jumpPower(370)
, m_startingPos(240, 754)
, m_hasGumboots(false)
, m_hasHiVis(false)
, m_hasLandP(false)
, m_coinsCounter(0)
, m_gumbootsTimer(0)
, m_hiVisTimer(0)
, MAX_GUMBOOTS_DURATION(10)
, MAX_HIVIS_DURATION(20)
, m_vecPlayerStates()
, m_stateManager()
, m_dustEmitter()
{
	Entity::Entity();
	
	m_stateManager.Initialise(this);

	//initialise the invincibilty circle
	m_pInvincibilityCircle = SpriteManager::GetInstance().CreateSprite("assets\\invincibilitycircle.png");
	m_pInvincibilityCircle->SetAlpha(100);

	//initialise dust emitter
	m_dustEmitter.InitialiseParticles();
	
	//Initialise Current sprite
	m_pCurrentSprite = new AnimatedSprite();
	m_pCurrentSprite->SetTotalFrames(4);
	m_pCurrentSprite->SetFrameSpeed(0.2f);
	m_pCurrentSprite->SetFrameWidth(100);
	m_pCurrentSprite->SetFrameHeight(100);
	m_pCurrentSprite->SetX(m_startingPos.GetXi());
	m_pCurrentSprite->SetY(m_startingPos.GetYi());
	m_pCurrentSprite->Initialise(*SpriteManager::GetInstance().GetSprite("assets\\PlayerSpriteSheetV2.png")->GetTexture(), 300);

	//Initialise this entity with sprite
	this->Initialise(m_pCurrentSprite);
	
	m_vecPlayerStates.push_back(m_stateManager.GetFallingState());
	
	//Position kiwi at starting position
	m_position.x = m_startingPos.x;
	m_position.y = m_startingPos.y;

	m_jumpPower = 350;

	//Load in the laserbeam sprite
	m_pLaserBeamSprite = SpriteManager::GetInstance().CreateSprite("assets//laserbeam.png");

}

Player::~Player()
{
	delete m_pCurrentSprite;
	m_pCurrentSprite = 0;

	//Delete remaining lasers
	for (auto laserbeam : m_pLaserBeams)
	{
		delete laserbeam;
		laserbeam = nullptr;
	}

	for (auto powerup : m_pPowerUps)
	{
		delete powerup;
		powerup = nullptr;
	}
}

void 
Player::Process(float deltaTime)
{
	if (!m_dead)
	{
		ProcessPowerUps(deltaTime);

		//process sprite animation
		m_pSprite->Process(deltaTime);

		m_vecPlayerStates.back()->Process(deltaTime);

		m_dustEmitter.Process(deltaTime);

		//Process laserbeams
		std::list<LaserBeam*> deadLaserBeams;
		for (auto laserbeam : m_pLaserBeams)
		{
			//First check if its dead
			if (laserbeam->IsDead())
			{
				deadLaserBeams.push_back(laserbeam);
			}
			else
			{
				//Get a list of enemies
				std::list<Enemy*> sectionEnemies;
				for (auto section : PlayState::GetInstance()->m_pSectionManager->m_activeSections)
				{
					for (auto enemy : section->GetEnemies())
					{
						sectionEnemies.push_back(enemy);
					}
				}

				//Process laserbeam and give it list of enemies
				laserbeam->Process(deltaTime, sectionEnemies);
			}
		}
		for (auto deadLaser : deadLaserBeams)
		{
			m_pLaserBeams.remove(deadLaser);
			delete deadLaser;
			deadLaser = 0;
		}

	}
}


void
Player::Draw(BackBuffer& backBuffer)
{
	//Draw debug text
	DrawPlayerDebugText(backBuffer);

	m_vecPlayerStates.back()->Draw(backBuffer);
	m_dustEmitter.Draw(backBuffer);

	if (m_hasHiVis)
	{
		m_pInvincibilityCircle->Draw(backBuffer);
	}

	//Draw all lasers
	for (auto laserbeam : m_pLaserBeams)
	{
		laserbeam->Draw(backBuffer);
	}

	Entity::Draw(backBuffer);
}

// Movement methods
void 
Player::MoveLeft()
{
	//Update position
	m_velocity.x = -m_movementSpeed;
}
void 
Player::MoveRight()
{
	//Update position
	m_velocity.x = m_movementSpeed;
}

void 
Player::Jump()
{
	//Add initial jump velocity
	m_velocity.y -= m_jumpPower;
}

void 
Player::SetGumboots(bool hasGumboots)
{
	m_hasGumboots = hasGumboots;
}

void 
Player::SetHiVis(bool hasHiVis)
{
	m_hasHiVis = hasHiVis;
}

bool 
Player::hasHiVis()
{
	return m_hasHiVis;
}

void 
Player::SetLandP(bool hasLandP)
{
	//set L&P
	//if true can skip enemy collisions 
	m_hasLandP = hasLandP;

	//if L&P being set to true
	if (hasLandP)
	{
		//change jump power, jump, then change back to normal 
		//m_jumpPower = 1500;
		SetVerticalVelocity(-1500);
		//Jump();
		//m_jumpPower = 370;
		// set to LANDPstate for animation (can just use jumpingstate if no separate animation
		m_vecPlayerStates.push_back(m_stateManager.GetLandPState());
	}
}

bool 
Player::hasLandP()
{
	return m_hasLandP;
}

int 
Player::GetCoins()
{
	return m_coinsCounter;
}

void 
Player::SetCoins(int coins)
{
	m_coinsCounter += coins;
}

DustParticleEmitter & 
Player::GetDustEmitter()
{
	return m_dustEmitter;
}

AnimatedSprite * 
Player::GetCurrentSprite()
{
	return m_pCurrentSprite;
}

void 
Player::SetCurrentSprite(AnimatedSprite * currentSprite)
{
	this->Initialise(currentSprite);
	//m_pCurrentSprite = currentSprite;
}

void 
Player::UpdatePosition(float deltaTime)
{
	m_position += m_velocity * deltaTime; //Update position based on velocity
}

float
Player::GetGravity()
{
	return 	m_gravity;
}

void 
Player::ApplyGravity()
{
	m_velocity.y += m_gravity;	//Simulate gravity
}

void 
Player::DrawPlayerDebugText(BackBuffer& backBuffer)
{
	//Only draw if debug mode is on
	if (PlayState::GetInstance()->GetDrawDebug())
	{
		char buffer[128];
		backBuffer.SetTextColour(Colour(255, 0, 0));
		//Draw X pos
		sprintf(buffer, "%s", "X: ");
		sprintf(buffer + strlen(buffer), "%f", m_position.x);
		backBuffer.DrawText(0, 0, buffer);
		//Draw Y pos
		sprintf(buffer, "%s", "Y: ");
		sprintf(buffer + strlen(buffer), "%f", m_position.y);
		backBuffer.DrawText(0, 30, buffer);
		//Draw VelocityX 
		sprintf(buffer, "%s", "VelX: ");
		sprintf(buffer + strlen(buffer), "%f", m_velocity.x);
		backBuffer.DrawText(0, 60, buffer);
		//Draw VelocityY
		sprintf(buffer, "%s", "VelY: ");
		sprintf(buffer + strlen(buffer), "%f", m_velocity.y);
		backBuffer.DrawText(0, 90, buffer);
		//Draw Player direction
		if (GetDirection() == RIGHT)
		{
			sprintf(buffer, "%s", "Direction: RIGHT");
			backBuffer.DrawText(0, 180, buffer);
		}
		else if (GetDirection() == LEFT)
		{
			sprintf(buffer, "%s", "Direction: LEFT");
			backBuffer.DrawText(0, 180, buffer);
		}

		if (IsDead())
		{
			sprintf(buffer, "%s", "Dead =(");
			backBuffer.DrawText(0, 240, buffer);
		}
	}
}

void 
Player::HandleInput(SDL_Keycode key)
{
	if (!IsDead())
	{
		m_vecPlayerStates.back()->HandleInput(key);

		//Shooting
		if (key == SDLK_UP || key == SDL_CONTROLLER_BUTTON_Y)
		{
			LaserBeam* newLaserBeam = new LaserBeam();
			newLaserBeam->Initialise(m_pLaserBeamSprite, this, LaserBeam::Direction::UP);
			m_pLaserBeams.push_back(newLaserBeam);
			SoundManager::GetInstance().PlayShootSFX();
		}
		if (key == SDLK_RIGHT || key == SDL_CONTROLLER_BUTTON_B)
		{
			LaserBeam* newLaserBeam = new LaserBeam();
			newLaserBeam->Initialise(m_pLaserBeamSprite, this, LaserBeam::Direction::RIGHT);
			m_pLaserBeams.push_back(newLaserBeam);
			SoundManager::GetInstance().PlayShootSFX();
		}
		if (key == SDLK_LEFT || key == SDL_CONTROLLER_BUTTON_X)
		{
			LaserBeam* newLaserBeam = new LaserBeam();
			newLaserBeam->Initialise(m_pLaserBeamSprite, this, LaserBeam::Direction::LEFT);
			m_pLaserBeams.push_back(newLaserBeam);
			SoundManager::GetInstance().PlayShootSFX();
		}
	}	
	if (key == SDLK_F1)
	{
		//Debug drawing - only accessible from PC
		PlayState::GetInstance()->ToggleDrawDebug();
	}
	if (key == SDLK_F2)
	{
		HiVisPowerUp* newHiVis = new HiVisPowerUp();
		newHiVis->ActivatePickUp(this);
		m_pPowerUps.push_back(newHiVis);
	}
}

bool
Player::CheckOnScreen()
{
	bool onScreen = false;

	if (GetPosition().GetYi() >= 830)
	{
		onScreen = true;
	}

	return onScreen;
}

void 
Player::ChangePlayerState(PlayerStates * state)
{
	if (!m_vecPlayerStates.empty())
	{
		//May need to perform any cleanups reuqired
		m_vecPlayerStates.pop_back();
	}

	// May need to perfrom any initialisations required 
	m_vecPlayerStates.push_back(state);
}

StateManager&
Player::GetStateManager()
{
	return m_stateManager;
}

Player::Direction
Player::GetDirection()
{
	return m_currentDirection;
}

void Player::SetDirection(Direction direction)
{
	m_currentDirection = direction;
}

void
Player::ProcessPowerUps(float deltaTime)
{
	if (m_hasGumboots)
	{
		m_gumbootsTimer += deltaTime;

		if (m_gumbootsTimer > MAX_GUMBOOTS_DURATION)
		{
			m_gumbootsTimer = 0;
			m_hasGumboots = false;
			m_jumpPower = 370;
		}
		else
		{
			m_jumpPower = 600;
		}
	}
	if (m_hasHiVis)
	{
		m_hiVisTimer += deltaTime;

		m_pInvincibilityCircle->SetX(this->GetPosition().GetXi());
		m_pInvincibilityCircle->SetY(this->GetPosition().GetYi());

		if (m_hiVisTimer > MAX_HIVIS_DURATION)
		{
			m_hiVisTimer = 0;
			m_hasHiVis = false;
		}	
	}


}