// COMP710 GP 2D Framework 2020
#ifndef __KIWICOIN_H__
#define __KIWICOIN_H__

//Local includes
#include "vector2.h"
#include "pickups.h"

// Forward Declarations:
class BackBuffer;
class Player;

class KiwiCoin : public PickUps
{
	//Member Methods:
public:
	KiwiCoin();
	~KiwiCoin();

	void ActivatePickUp(Player* player);


protected:

private:

	//Member Data:
public:

protected:

private:

};

#endif //__KIWICOIN_H__
