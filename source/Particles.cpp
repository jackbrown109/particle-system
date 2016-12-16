//===========================================================================
// File: Particles.cpp
// Author: Jack Brown
// Date Created: 3/12/16
//===========================================================================

#include "Particles.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//===========================================================================
// Default Constructor 
//===========================================================================
Particles::Particles()
{
	state = new uState();
}

//===========================================================================
// Copy Constructor 
//===========================================================================
Particles::Particles(const Particles & a_particle)
{
	state = new uState();
}

//===========================================================================
// Initialise
//===========================================================================
Particles::Particles(const glm::vec4 a_particlePosition, const float a_velocity, const glm::vec4 a_colour, const glm::vec4 a_particleDirection, float a_lifeSpan)
{
	state = new uState();
}


//===========================================================================
// Destructor
//===========================================================================
Particles::~Particles()
{
	delete state;
}

//===========================================================================
// Initialise function puts the particle into a live state
//===========================================================================
void Particles::Initialise(const glm::vec4 a_particlePosition, const float a_velocity, const glm::vec4 a_colour,const glm::vec4 a_particleDirection, float a_lifeSpan)
{
	state->_live.m_particlePosition = a_particlePosition;
	state->_live.m_velocity = a_velocity;
	state->_live.m_colour = a_colour;
	state->_live.m_particleDirection = a_particleDirection;
	state->_live.m_lifeSpan = a_lifeSpan * a_particleDirection.y;
}

//===========================================================================
// Update function called once per frame used to animate the particle 
//===========================================================================
bool Particles::UpdateAndCheckAlive(const float a_deltaTime)
{
	m_iParticleDecay += a_deltaTime;
	
	if (!IsAlive()) return false;
	if (m_iParticleDecay < state->_live.m_lifeSpan)
	{
		//m_iParticleDecay--;
		state->_live.m_particlePosition += state->_live.m_velocity * a_deltaTime;
		//state._live.m_dPosY += state._live.m_dVelocityY;
		//return m_iParticleDecay == 0;
		return true;
	}
}

//===========================================================================
// IsAlive bool used so we know which particles are available for reuse.
// Uses the m_iParticleDecay variable to discover which particles are in use.
//===========================================================================
bool Particles::IsAlive() const
{
	return m_iParticleDecay > 0;
}

//===========================================================================
// GetNext function gets the next available particle in the list
//===========================================================================
Particles* Particles::GetNext() const
{
	return state->next;
}

//===========================================================================
// SetNext function sets the next available particle
//===========================================================================
void Particles::SetNext(Particles* next)
{
	state->next = next;
}

//===========================================================================
// GetPosition function gets the position of the emitted particle
//===========================================================================
glm::vec4 Particles::GetPosition() const
{
	return state->_live.m_particlePosition;
}


//===========================================================================
// GetDirection function gets the direction of the emitted particle
//===========================================================================
glm::vec4 Particles::GetDirection() const
{
	return state->_live.m_particleDirection;
}

//===========================================================================
// GetColour function gets the colour of the emitted particle
//===========================================================================
glm::vec4 Particles::GetColour() const
{
	return state->_live.m_colour;
}