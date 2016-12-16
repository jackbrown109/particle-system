//===========================================================================
// File: ParticlePool.cpp
// Author: Jack Brown
// Date Created: 3/12/16
//===========================================================================

#include "ParticlePool.h"
#include "Particles.h"
#include <iostream>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//===========================================================================
// Default Constructor
//===========================================================================
ParticlePool::ParticlePool()
{
	// The first particle is available
	pFirstAvailable = &particles[0];

	// Each Particle points to the next
	for (int i = 0; i < MAX_PARTICLES - 1; i++)
	{
		particles[i].SetNext(&particles[i + 1]);
	}

	// The last particle terminates the list
	particles[MAX_PARTICLES - 1].SetNext(NULL);
}

//===========================================================================
// Destructor
//===========================================================================
ParticlePool::~ParticlePool()
{

}

//===========================================================================
// Create function lets external code create new particles
//===========================================================================
void ParticlePool::Create(const glm::vec4 a_particlePosition, const float a_velocity, const glm::vec3 a_particleDirection, int a_lifeSpan)
{
	// Checks to see if the pool isn't full  
	assert(pFirstAvailable != NULL);

	// Remove the particle from the available list
	Particles* pNewParticle = pFirstAvailable;
	pNewParticle->GetNext(pFirstAvailable);

	// Initialise the particle
	pNewParticle->Initialise(a_particlePosition, a_velocity, a_particleDirection, a_lifeSpan);

}

//===========================================================================
// Update function called once per frame used to animate each particle in
// the pool.
//===========================================================================
void ParticlePool::Update(const float a_deltaTime)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (particles[i].UpdateAndCheckAlive(a_deltaTime))
		{
			// Add this particle to the front of the list
			particles[i].SetNext(pFirstAvailable);
			pFirstAvailable = &particles[i];
		}
	}
}
