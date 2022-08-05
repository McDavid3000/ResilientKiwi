#ifndef _DUSTPARTICLEEMITTER_H_
#define _DUSTPARTICLEEMITTER_H_

#include "particleemitter.h"
#include "particle.h"

class DustParticleEmitter : public ParticleEmitter
{
	//member methods
public:
	DustParticleEmitter();
	~DustParticleEmitter();

	void SpawnParticles();

	void InitialiseParticles();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	//member data
public:

protected:
	int m_dustParticlesArrSize;
	Particle m_arrDustParticles[50];

private:

};

#endif _DUSTPARTICLEEMITTER_H_