// COMP710 GP 2D Framework 2020
#ifndef __LANDPPOWERUP_H__
#define __LANDPPOWERUP_H__

//Local includes
#include "vector2.h"
#include "pickups.h"

// Forward Declarations:
class BackBuffer;

class LandPPowerUp : public PickUps
{
	//Member Methods:
public:
	LandPPowerUp();
	~LandPPowerUp();

	void ActivatePickUp(Player* player);

protected:

private:

	//Member Data:
public:

protected:

private:

};

#endif //__LANDPPOWERUP_H__
