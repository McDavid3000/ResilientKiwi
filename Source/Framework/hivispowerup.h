// COMP710 GP 2D Framework 2020
#ifndef __HIVISPOWERUP_H__
#define __HIVISPOWERUP_H__

//Local includes
#include "vector2.h"
#include "pickups.h"
#include "player.h"

// Forward Declarations:
class BackBuffer;

class HiVisPowerUp : public PickUps
{
	//Member Methods:
public:
	HiVisPowerUp();
	~HiVisPowerUp();

	void ActivatePickUp(Player* player);

protected:

private:

	//Member Data:
public:

protected:

private:

};

#endif //__HIVISPOWERUP_H__
