#include "hivispowerup.h"
#include "soundmanager.h"

HiVisPowerUp::HiVisPowerUp()
{
}

HiVisPowerUp::~HiVisPowerUp()
{
}

void 
HiVisPowerUp::ActivatePickUp(Player * player)
{
	HiVisPowerUp::SetDead(true);
	player->SetHiVis(true);
	SoundManager::GetInstance().PlayPowerUpSFX();
}
