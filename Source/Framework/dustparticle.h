#ifndef _DUSTPARTICLE_H_
#define _DUSTPARTICLE_H_

#include "particle.h"

class DustParticle : public Particle
{
	//member methods
public:
	DustParticle();
	~DustParticle();

	void Process(float deltaTime);

protected:

private:

	//member data

public:

protected:

private:

};

#endif _DUSTPARTICLE_H_
