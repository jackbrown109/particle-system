#ifndef __Application_H_
#define __Application_H_

#include "Emitter.h"
#include "Particles.h"
#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class MyApplication : public Application
{
public:

	MyApplication();
	virtual ~MyApplication();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
	Emitter *Emitter1;
};

#endif // __Application_H_