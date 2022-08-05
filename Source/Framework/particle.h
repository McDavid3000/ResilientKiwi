#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "entity.h"

//forward declaration

class Particle : public Entity
{
	//member methods
public:
	Particle();
	~Particle();

	void Process(float deltaTime);

	void SetAlpha(unsigned char alpha);
	unsigned char GetAlpha();

protected:

private:

	//member data

public:

protected:

private:

};

#endif _PARTICLE_H_