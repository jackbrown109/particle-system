//===========================================================================
// File: Particles.h
// Author: Jack Brown
// Date Created: 3/12/16
//===========================================================================

//===========================================================================
// Things to include for particles:
// - Size
// - Position
// - Velocity (speed in a direction)
// - Life Span
//===========================================================================

#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include <glm/glm.hpp>
#include <glm/ext.hpp>


//State when particle is in use
struct live // Holds the particles state when it's being animated
{
	live() {}; //constructor
	live(const live& a_live) {}; // copy constructor
	~live() {}; //destructor
	live operator=(const live& a_live) {}; //operator
	
	glm::vec4 m_particlePosition; //position of the particle
	glm::vec4 m_particleDirection; // direction of the emitted particle
	glm::vec4 m_colour; // Colour of emitted particles
	float m_velocity; // Velocity of the particle
	float m_lifeSpan; // How long the particle will live
	bool bIsAlive;

};

class Particles
{
	friend class ParticlePool; // Allows ParticlePool access to privates

public:

	//Default constructor
	Particles();
	// Copy Constructor
	Particles(const Particles& a_particle);
	// Destructor
	~Particles();
	// Goes to initialise
	Particles(const glm::vec4 a_particlePos, const float a_velocity, const glm::vec4 a_colour, const glm::vec4 a_particleDirection, float a_lifeSpan);


	// Declare the Initialise function in Particles.cpp
	void Initialise(const glm::vec4 a_particlePosition, const float a_velocity, const glm::vec4 a_colour, const glm::vec4 a_particleDirection, float a_lifeSpan);
	// Declare the Update function in Particles.cpp
	bool UpdateAndCheckAlive(const float a_deltaTime);

	// Declare the bool IsAlive
	bool IsAlive() const;

	//GetNext and SetNext gets and sets the particle's position
	Particles* GetNext() const;
	void SetNext(Particles* next);

	// GetPosition gets position of particle
	glm::vec4 GetPosition() const;
	// SetPosition sets position of particle
	void SetPosition(glm::vec4 a_particlePosition) const;

	// GetDirection gets direction of emitted particle
	glm::vec4 GetDirection() const;
	// SetDirection sets direction of emitted particle
	void SetDirection(glm::vec4 a_particlePosition) const;

	// GetColour gets colour of emitted particle
	glm::vec4 GetColour() const;
	

protected:
	
	

	struct uState
	{
		// Reference to the live struct
		live _live;

		Particles* next; // Pointer to the next available particle	
	};
	uState* state;

private:
	int m_iParticleDecay; // How long until particle will be at the end of it's lifespan
	



};
#endif  //__PARTICLES_H__