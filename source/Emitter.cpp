//===========================================================================
// File: Emitter.cpp
// Author: Jack Brown
// Date Created: 3/12/16
//===========================================================================

#include "Emitter.h"
#include "Particles.h"
#include "ParticlePool.h"
#include "Gizmos.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//===========================================================================
// Constructor
//===========================================================================
Emitter::Emitter(const glm::vec4& a_emitterPosition, float a_fVelocity, const glm::vec3& a_emitterDirection, float a_fLifeSpan)
{
	Initialise(a_emitterPosition, a_fVelocity, a_emitterDirection, a_fLifeSpan);
}

//===========================================================================
// Copy Constructor
//===========================================================================
Emitter::Emitter(const Emitter& a_Emitter)
{

}

//===========================================================================
// Virtual Destructor
//===========================================================================
Emitter::~Emitter()
{
	
}

//===========================================================================
// Initialise the emitter
//===========================================================================
void Emitter::Initialise(const glm::vec4& a_emitterPosition, float a_fVelocity, const glm::vec3& a_emitterDirection, float a_fLifeSpan)
{
	m_emitterPosition = a_emitterPosition;
	m_fVelocity = a_fVelocity;
	m_emitterDirection = a_emitterDirection;
	m_fLifeSpan = a_fLifeSpan;
	m_iParticleDecay = 0;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_pParticles[i] = nullptr;
	}
}

//===========================================================================
// Update
//===========================================================================
void Emitter::Update(const float a_deltaTime, glm::mat4 a_camera)
{
	Particles *p;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (!m_pParticles[i])//if it's null
		{
			p = m_pParticles[i];
			m_pParticles[i] = new Particles();
			m_pParticles[i]->Initialise(m_emitterPosition, m_fVelocity, m_emitterDirection, m_fLifeSpan);
			
			Draw(m_pParticles[i]->GetPosition(), glm::vec4(1, 1, 1, 1), a_camera);
		}

		if (m_pParticles[i] != nullptr)
		{
			if (!m_pParticles[i]->UpdateAndCheckAlive(a_deltaTime))
			{
				delete m_pParticles[i];
				m_pParticles[i] = nullptr;
			}
			/*else
			{
				Draw(m_pParticles[i]->GetPosition(), glm::vec4(1, 1, 1, 1), a_camera);
			}*/
		}

	}
}

Particles* Emitter::getParticle(int index)
{
	if (m_pParticles[index])
	{
		return m_pParticles[index];
	}
	return nullptr;
}

void Emitter::Draw(glm::vec4& a_position, glm::vec4& a_colour, glm::mat4& a_camera)
{
	Gizmos::addBillboard(a_position, a_colour, glm::vec2(0.1f, 0.1f), a_camera);
}