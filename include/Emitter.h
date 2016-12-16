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
	Emitter(const glm::vec4& a_emitterPosition, float a_fVelocity, const glm::vec3& a_emitterDirection, float a_fLifeSpan);
	// Copy Constructor
	Emitter(const Emitter& a_Emitter);
	// Virtual Destructor- Virtual so child classes will call it upon their destruction
	virtual ~Emitter();

	// Declare the initialise function in Emitter.cpp
	void Initialise(const glm::vec4& a_emitterPosition, float a_fVelocity, const glm::vec3& a_emitterDirection, float a_fLifeSpan);
	//Declare the update function in Emitter.cpp
	void Update(const float a_deltaTime, glm::mat4 a_camera);

	Particles* getParticle(int index);

	void Draw(glm::vec4& a_position, glm::vec4& a_colour, glm::mat4& a_camera);

protected:
	
private:

	Particles* m_pParticles[MAX_PARTICLES];

	glm::vec4 m_emitterPosition;
	glm::vec3 m_emitterDirection;

	float m_fVelocity;
	float m_fLifeSpan;
	float m_iParticleDecay;
};

#endif //__EMITTER_H__