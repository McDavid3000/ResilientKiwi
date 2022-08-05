#include "gumbootpowerup.h"
#include "player.h"
#include "soundmanager.h"

GumbootPowerUp::GumbootPowerUp()
{
}

GumbootPowerUp::~GumbootPowerUp()
{
}

void GumbootPowerUp::ActivatePickUp(Player * player)
{
	this->SetDead(true);
	player->SetGumboots(true);
	SoundManager::GetInstance().PlayPowerUpSFX();
}
