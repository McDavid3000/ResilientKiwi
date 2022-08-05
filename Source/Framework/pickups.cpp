// This include:
#include "pickups.h"

// Local includes:
#include "player.h"
#include "entity.h"
#include "sprite.h"

// Library includes:
#include <cmath>

PickUps::PickUps()
	:m_sparkleEmitter()
{
	m_sparkleEmitter.InitialiseParticles();
}

void 
PickUps::Process(float deltaTime)
{
	if (!this->IsDead())
	{
		Entity::Process(deltaTime);
		m_sparkleEmitter.Process(deltaTime);
	}
}

void
PickUps::Draw(BackBuffer& backBuffer)
{
	if (!this->IsDead())
	{
		Entity::Draw(backBuffer);
		m_sparkleEmitter.Draw(backBuffer);
	}
}

PickUps::~PickUps()
{
}

bool 
PickUps::CheckPlayerCollision(Player* player)
{
	if (!player->IsDead())
	{
		bool colliding = false;

		if (!this->IsDead())
		{
			struct Circle
			{
				float px;
				float py;
				float radius;
			};

			Circle thisCircle;
			Circle eCircle;

			//checking collision circle based on height. won't work well if pickup h and w aren't even
			thisCircle.radius = float(m_pSprite->GetHeight() / 2);
			eCircle.radius = float(player->GetHeight() / 2);

			float x = GetCentrePosition().x - player->GetCentrePosition().x;
			float y = GetCentrePosition().y - player->GetCentrePosition().y;

			float hypotenuse = hypot(x, y);

			if ((thisCircle.radius + eCircle.radius) >= hypotenuse)
			{
				colliding = true;
				this->ActivatePickUp(player);
			}
		}

		return colliding;
	}
	return false;
}

void 
PickUps::SetRelativePosition(Vector2 position)
{
	m_position = position;
	m_relativePos = position;

	//set sparkle emitter location
	m_sparkleEmitter.SetPosition(this->GetCentrePosition());
}

void 
PickUps::UpdatePosition(Vector2 position)
{
	m_position += position;
	m_sparkleEmitter.SetPosition(this->GetCentrePosition());
}

void 
PickUps::ResetPosition(Vector2 sectionPosition)
{
	m_position = sectionPosition + m_relativePos;
	m_sparkleEmitter.SetPosition(this->GetCentrePosition());
}

void
PickUps::SetSectionPlatforms(std::list<Platform*> sectionPlatforms)
{
	m_pSectionPlatforms = sectionPlatforms;
}


