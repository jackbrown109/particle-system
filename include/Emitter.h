//===========================================================================
// File: Emitter.h
// Author: Jack Brown
// Date Created: 3/12/16
//===========================================================================

//===========================================================================
// Things to include for emitter:
// - Position
// - Direction
// - Spawn Rate
// - Spread
//===========================================================================

#ifndef __EMITTER_H__
#define __EMITTER_H__


#include "ParticlePool.h"
#include "Particles.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>



class Emitter
{
	
public:
	// Constructor
	Emitter(const glm::vec4& a_emitterPosition, float a_fVelocity, const glm::vec4 a_colour, const glm::vec4& a_emitterDirection, glm::vec4 a_spread, float a_fLifeSpan);
	// Copy Constructor
	Emitter(const Emitter& a_Emitter);
	// Virtual Destructor- Virtual so child classes will call it upon their destruction
	virtual ~Emitter();

	// Declare the initialise function in Emitter.cpp
	void Initialise(const glm::vec4& a_emitterPosition, float a_fVelocity, const glm::vec4 a_colour, const glm::vec4& a_emitterDirection, glm::vec4 a_spread, float a_fLifeSpan);
	//Declare the update function in Emitter.cpp
	void Update(const float a_deltaTime, glm::mat4 a_camera);

	//Declare the GetPosition function
	glm::vec4 GetPosition() const;
	//Declare the GetDirection function
	glm::vec4 GetDirection() const;
	
	//Declare the getParticle function
	Particles* getParticle(int index);

	//Declare the getRandomDirection function
	glm::vec4 getRandomDirection();

	//Declare the Draw function
	void Draw(glm::vec4& a_position, glm::vec4& a_colour, glm::mat4& a_camera);

protected:
	
private:

	Particles* m_pParticles[MAX_PARTICLES];

	glm::vec4 m_emitterPosition; //Position of the emitter
	glm::vec4 m_emitterDirection; //Direction of set by emitter for emitted particles
	glm::vec4 m_colour; //Colour of particle
	float m_fVelocity; //Velocity of particles
	float m_fLifeSpan; // How long the particle will be alive
	float m_iParticleDecay; // Value for when particles die
	glm::vec4 m_spread; // Max random values for particle spawning
};

#endif //__EMITTER_H__