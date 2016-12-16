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
struct live//  Holds the particles state when it's being animated
{
	live() {};
	live(const live& a_live) {};
	~live() {};
	live operator=(const live& a_live)
	{};
	//Particles(glm::vec3 a_particlePos, float a_velocity, glm::vec3 a_particleDirection, float a_lifeSpan);
	//double m_dPosX, m_dPosY; // X and Y positions of the particle
	//double m_dVelocityX, m_dVelocityY; // X and Y Velocities of the particle
	glm::vec4 m_particlePosition; //position of the particle
	glm::vec3 m_particleDirection; // direction of the emitted particle
	float m_lifeSpan;
	float m_velocity; // Velocity of the particle
	
};

class Particles
{
	friend class ParticlePool; // Allows ParticlePool access to privates

public:

	//Default constructor
	Particles();
	Particles(const Particles& a_particle);

	Particles(const glm::vec4 a_particlePos, const float a_velocity, const glm::vec3 a_particleDirection, float a_lifeSpan);

	// Destructor
	~Particles();

	// Declare the Initialise function in Particles.cpp
	void Initialise(const glm::vec4 a_particlePosition, const float a_velocity, const glm::vec3 a_particleDirection, float a_lifeSpan);

	// Declare the Update function in Particles.cpp
	bool UpdateAndCheckAlive(const float a_deltaTime);

	// Declare the bool IsAlive
	bool IsAlive() const;

	//GetNext and SetNext gets and sets the particle's position
	
	void GetNext(Particles* i) const;
	void SetNext(Particles* next);

	// GetPosition gets position of particle
	
	glm::vec4 GetPosition() const;
	

	// GetDirection gets direction of emitted particle
	
	glm::vec3 GetDirection() const;
	

protected:
	
	

	struct uState
	{
		// Reference to the live struct
		live _live;

		// State when particle is unavailable
		Particles* next; // Pointer to the next available particle

		
	};
	uState* state;

private:
	int m_iParticleDecay; // How long until particle will be at the end of it's lifespan
	
	bool bIsAlive;




};
#endif  //__PARTICLES_H__