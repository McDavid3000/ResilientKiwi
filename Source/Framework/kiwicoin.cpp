#include "kiwicoin.h"
#include "pickups.h"
#include "player.h"
#include "soundmanager.h"

KiwiCoin::KiwiCoin()
{
}

KiwiCoin::~KiwiCoin()
{
}

void KiwiCoin::ActivatePickUp(Player * player)
{
	this->SetDead(true);
	player->SetCoins(1);
	SoundManager::GetInstance().PlayKiwiCoinSFX();
}


