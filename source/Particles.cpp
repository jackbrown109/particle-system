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
	SetPosition(a_particlePosition);
	state->_live.m_velocity = a_velocity;
	state->_live.m_colour = a_colour;
	SetDirection(a_particleDirection);
	state->_live.m_lifeSpan = a_lifeSpan;
	state->_live.bIsAlive = true;
	
}

//===========================================================================
// Update function called once per frame used to animate the particle 
//===========================================================================
bool Particles::UpdateAndCheckAlive(const float a_deltaTime)
{
	// Sets the particle decay value to deltaTime
	m_iParticleDecay += a_deltaTime;

	//std::cout << state->_live.m_lifeSpan << std::endl;

	// If lifeSpan reaches 0 
	if (m_iParticleDecay >= state->_live.m_lifeSpan)
	{
		//set the bIsAlive bool to false
		state->_live.bIsAlive = false;
		return false; // return false from UpdateAndCheckAlive
	}
	
	// If lifeSpan is greater than zero
	if (m_iParticleDecay <= state->_live.m_lifeSpan)
	{
		state->_live.m_lifeSpan--; // decrease lifespan
		
		// Positional update for the particle
		state->_live.m_particlePosition +=  state->_live.m_particleDirection * state->_live.m_velocity * a_deltaTime; 
		
		return true; // return true from UpdateAndCheckAlive
	}
	
}

//===========================================================================
// IsAlive bool used so we know which particles are available for reuse.
// Uses the m_iParticleDecay variable to discover which particles are in use.
//===========================================================================
bool Particles::IsAlive() const
{
	return state->_live.bIsAlive;
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
// SetPosition function sets the position of the emitted particle
//===========================================================================
void Particles::SetPosition(glm::vec4 a_particlePosition) const
{
	state->_live.m_particlePosition = a_particlePosition;
}


//===========================================================================
// GetDirection function gets the direction of the emitted particle
//===========================================================================
glm::vec4 Particles::GetDirection() const
{
	return state->_live.m_particleDirection;
}

//===========================================================================
// SetDirection function sets the direction of the emitted particle
//===========================================================================
void Particles::SetDirection(glm::vec4 a_particlePosition) const
{
	state->_live.m_particleDirection = glm::vec4(normalize(a_particlePosition));
}

//===========================================================================
// GetColour function gets the colour of the emitted particle
//===========================================================================
glm::vec4 Particles::GetColour() const
{
	return state->_live.m_colour;
}