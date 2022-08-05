//This include
#include "laserbeam.h"

//Local includes
#include "enemy.h"
#include "player.h"
#include "sprite.h"
#include "texture.h"
#include "soundmanager.h"

//Library includes

//Constructor
LaserBeam::LaserBeam()
	: m_laserSpeed(400)
	, m_laserDamage(40)
{
	Entity();
}

bool 
LaserBeam::Initialise(Sprite* sprite, Player* player, LaserBeam::Direction direction)
{
	//Set player reference
	m_pPlayer = player;

	//Set sprite
	m_pSprite = sprite;

	float offset = 0.0f;

	//Set velocity with direction
	switch (direction)
	{
	case LEFT:
		//Set starting position
		m_pPlayer->SetDirection(Player::Direction::LEFT);
		offset = 20.0f;
		SetPositionX(m_pPlayer->GetPosition().x + offset);
		SetPositionY(m_pPlayer->GetPosition().y);
		SetVelocity(Vector2(-m_laserSpeed, 0));
		m_laserRotationValue = 90;
		m_pSprite->GetTexture()->RotateTexture(m_laserRotationValue);
		break;
	case RIGHT:
		m_pPlayer->SetDirection(Player::Direction::RIGHT);
		offset = 80.0f;
		SetPositionX(m_pPlayer->GetPosition().x + offset);
		SetPositionY(m_pPlayer->GetPosition().y);
		SetVelocity(Vector2(m_laserSpeed, 0));
		m_laserRotationValue = 90;
		m_pSprite->GetTexture()->RotateTexture(m_laserRotationValue);
		break;
	case UP:
		SetPositionX(m_pPlayer->GetCentrePosition().x);
		SetPositionY(m_pPlayer->GetPosition().y);
		SetVerticalVelocity(-m_laserSpeed);
		m_laserRotationValue = 0;
		m_pSprite->GetTexture()->RotateTexture(m_laserRotationValue);
		break;
	}


	return Entity::Initialise(sprite);
}

void 
LaserBeam::Process(float deltaTime, std::list<Enemy*> enemyList)
{
	// Update position
	m_position += m_velocity * deltaTime; //Update position based on velocity

	//Check collision with enemy in the enemy list
	for (auto enemy : enemyList)
	{
		if (!enemy->IsDead())
		{
			if (IsCollidingWith(*enemy))
			{
				enemy->DeductHitpoints(m_laserDamage); //Damage the enemy
				SetDead(true); //Kill the laser
				SoundManager::GetInstance().PlayEnemyDeadSFX();
			}
		}
	}

	//Check if out of screen bounds
	int screenHeight = 854;
	int screenWidth = 480;
	
	if (GetPosition().x < 0 || GetPosition().x - m_pSprite->GetWidth() > screenWidth)
	{
		SetDead(true); //Horizontal check
	}
	else if (GetPosition().y < 0 || GetPosition().y > screenHeight)
	{
		SetDead(true); //Vertical check
	}

	Entity::Process(deltaTime);
}

bool
LaserBeam::IsCollidingWith(Entity& e)
{
	//Rectangle collision detection
	//Read Platform::CollidingWith for an explanation into the algorithm

	int thisX = m_position.GetXi();
	int thisY = m_position.GetYi();
	int thisW = m_pSprite->GetWidth();
	int thisH = m_pSprite->GetHeight();

	int foreignX = e.GetPosition().GetXi();
	int foreignY = e.GetPosition().GetYi();
	int foreignW = e.GetWidth();
	int foreignH = e.GetHeight();

	if (thisX + thisW >= foreignX &&
		thisX <= foreignX + foreignW &&
		thisY + thisH >= foreignY &&
		thisY <= foreignY + foreignH)
	{
		return true;
	}

	return false;
}

void 
LaserBeam::Draw(BackBuffer& backBuffer)
{
	m_pSprite->GetTexture()->RotateTexture(m_laserRotationValue);
	Entity::Draw(backBuffer);
}