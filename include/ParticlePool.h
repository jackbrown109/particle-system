//===========================================================================
// File: ParticlePool.h
// Author: Jack Brown
// Date Created: 3/12/16
//===========================================================================

#ifndef __PARTICLEPOOL_H__
#define __PARTICLEPOOL_H__

#include "Particles.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define MAX_PARTICLES 16384


class ParticlePool
{
public:
	// Default Constructor
	ParticlePool();
	// Destructor
	~ParticlePool();

	//Declare the Create function
	void Create(const glm::vec4 a_particlePosition, const float a_velocity, const glm::vec4 a_colour, const glm::vec4 a_particleDirection, int a_lifeSpan);
	//Declare the Update function
	void Update(const float a_deltaTime);

protected:

private:
	Particles particles[MAX_PARTICLES];

	Particles* pFirstAvailable;

};

template <class TObject>
class GenericPool
{
private:
	TObject particles[MAX_PARTICLES];
	bool    bIsAlive[MAX_PARTICLES];
};

#endif // __PARTICLEPOOL_H__

