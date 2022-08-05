#ifndef _SPARKLEEMITTER_H_
#define _SPARKLEEMITTER_H_

#include "particleemitter.h"
#include "particle.h"

class SparkleEmitter : public ParticleEmitter
{
	//member methods
public:
	SparkleEmitter();
	~SparkleEmitter();

	void SpawnParticles();

	void InitialiseParticles();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	//member data
public:

protected:
	int m_sparkleArrSize;
	float m_timeElapsed;
	Particle m_arrSparkles[100];

private:

};

#endif _SPARKLEEMITTER_H_