// COMP710 GP 2D Framework 2020
#ifndef __GUMBOOTPOWERUP_H__
#define __GUMBOOTPOWERUP_H__

//Local includes
#include "vector2.h"
#include "pickups.h"

// Forward Declarations:
class BackBuffer;

class GumbootPowerUp : public PickUps
{
	//Member Methods:
public:
	GumbootPowerUp();
	~GumbootPowerUp();
	void ActivatePickUp(Player* player);

protected:

private:

	//Member Data:
public:

protected:

private:

};

#endif //__GUMBOOTPOWERUP_H__
