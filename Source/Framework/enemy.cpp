// This include:
#include "enemy.h"

// Local includes:
#include "sprite.h"
#include "platform.h"

// Library includes


Enemy::Enemy()
: m_movementSpeed(0)
{
	Entity::Entity();
}

Enemy::~Enemy()
{
	
}

void 
Enemy::Process(float deltaTime)
{
	if (!IsDead())
	{
		//Set movement speed if hasnt been set yet
		if (m_movementSpeed == NULL)
		{
			switch (m_movementSpeedCategory)
			{
			case EnemySpeed::SLOW:
				m_movementSpeed = 10;
				break;
			case EnemySpeed::MEDIUM:
				m_movementSpeed = 30;
				break;
			case EnemySpeed::FAST:
				m_movementSpeed = 50;
				break;
			default:
				m_movementSpeed = 10;
			}
		}

		// Update position
		m_position += m_velocity * deltaTime; //Update position based on velocity

		ProcessAI(deltaTime);

		Entity::Process(deltaTime);
	}
}

void 
Enemy::Draw(BackBuffer& backBuffer)
{
	if (!IsDead())
	{
		Entity::Draw(backBuffer);

	}
}

//***************//

void 
Enemy::UpdatePosition(Vector2 position)
{
	m_position += position;
}

void 
Enemy::ResetPosition(Vector2 sectionPosition)
{
	m_position = sectionPosition + m_relativePos;
}

void 
Enemy::SetRelativePosition(Vector2 position)
{
	m_position = position;
	m_relativePos = position;
}

Vector2 
Enemy::GetRelativePosition()
{
	return m_relativePos;
}

bool 
Enemy::IsCollidingWith(Entity& e)
{
	if (!IsDead())
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
	return false;
}

bool Enemy::IsCollidingWith(int x, int y, int w, int h)
{
	if (!IsDead())
	{
		int platformX = m_position.GetXi();
		int platformY = m_position.GetYi();
		int platformW = m_pSprite->GetWidth();
		int platformH = m_pSprite->GetHeight() / 5; //Need to only check the top third of the platform

		if (platformX + platformW >= x &&
			platformX <= x + w &&
			platformY + platformH >= y &&
			platformY <= y + h)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void 
Enemy::DeductHitpoints(int hitpoints)
{
	m_hitpoints -= hitpoints;

	if (m_hitpoints <= 0)
	{
		SetDead(true);
	}
}

struct Circle
{
	float centreX;
	float centreY;
	float radius;
};

bool 
Enemy::IsCircleCollidingWith(Entity& e)
{
	if (!IsDead())
	{
		Circle thisEntity;
		thisEntity.centreX = GetPosition().x;
		thisEntity.centreY = GetPosition().y;
		thisEntity.radius = m_pSprite->GetWidth() / 3.0f;

		Circle eEntity;
		eEntity.centreX = e.GetPosition().x;
		eEntity.centreY = e.GetPosition().y;
		eEntity.radius = e.GetSprite()->GetWidth() / 3.0f;

		//Find the distance between circle centre points
		float yDistance = thisEntity.centreY - eEntity.centreY;
		float xDistance = thisEntity.centreX - eEntity.centreX;
		if (yDistance < 0) { yDistance = yDistance * -1; } //Make positive number if not
		if (xDistance < 0) { xDistance = xDistance * -1; }
		float distance = sqrt((pow(xDistance, 2)) + (pow(yDistance, 2)));
		//Subtract the radii of the two circles
		distance -= thisEntity.radius;
		distance -= eEntity.radius;
		bool isColliding;
		if (distance <= 0)
		{
			isColliding = true;
		}
		else
		{
			isColliding = false;
		}

		return (isColliding);
	}
	return false;
}

void 
Enemy::SetSectionPlatforms(std::list<Platform*> sectionPlatforms)
{
	m_pSectionPlatforms = sectionPlatforms;
}


void Enemy::ProcessAI(float deltaTime)
{

}

void 
Enemy::SetAIState(AIState state)
{
	m_pCurrentAIState = state;
}

int 
Enemy::GetMovementSpeed()
{
	return m_movementSpeed;
}