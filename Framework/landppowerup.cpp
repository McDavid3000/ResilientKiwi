#include "landppowerup.h"
#include "player.h"
#include "soundmanager.h"

LandPPowerUp::LandPPowerUp()
{
}

LandPPowerUp::~LandPPowerUp()
{
}

void LandPPowerUp::ActivatePickUp(Player * player)
{
	this->SetDead(true);
	player->SetLandP(true);
	SoundManager::GetInstance().PlayPowerUpSFX();
}
