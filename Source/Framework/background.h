#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

// Local includes:
#include "entity.h"

// Forward Declarations:
class Sprite;
class BackBuffer;

class Background : public Entity
{
	//Member Methods:
public:
	Background();
	~Background();

protected:

private:
	Background(const Background& bg);
	Background& operator=(const Background& bg);

	//Member Data:
public:

protected:

private:

};

#endif __BACKGROUND_H__
