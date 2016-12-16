#include "MyApplication.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "TextureManager.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

MyApplication::MyApplication()
{

}

MyApplication::~MyApplication()
{

}

bool MyApplication::onCreate(int a_argc, char* a_argv[])
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// Sets the values stored by the Emitter
	Emitter1 = new Emitter(
		glm::vec4(0, 0, 0, 0), //Position
		5.f, //Velocity
		glm::vec4(1, 1, 1, 0.1f), // Colour
		glm::vec4(0.f, 1.f, 0.f, 0.f), //Direction - x,y,z,w
		glm::vec4(0.6f, 0.5f, 0.6f, 0.f), // Spread
		1000.f * glm::linearRand(-1.f, 1.f)); //LifeSpan

	

	//Initialise our Texture Manager class
	TextureManager* texManager = TextureManager::CreateInstance();
	unsigned int texID = texManager->LoadTexture("./images/01_angry_beyonce.jpg");
	unsigned int texID2 = texManager->LoadTexture("./images/01_angry_beyonce.jpg");
	unsigned int texID3 = texManager->LoadTexture("./images/01_angry_beyonce.jpg");

	texManager->ReleaseTexture(texID2);
	texManager->ReleaseTexture(texID3);
	texManager->ReleaseTexture(texID);

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	return true;
}

void MyApplication::onUpdate(float a_deltaTime)
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// Sets a pointer to the particles class
	Particles *p;
	// Calls update in the Emitter class
	Emitter1->Update(a_deltaTime, m_cameraMatrix);

	// For each particle in the array
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		//get a particle
		p = Emitter1->getParticle(i);
		if (p)
		{
			// If the particle is alive
			if (p->IsAlive())
			{
				// Call the draw function in the Emitter class 
				Emitter1->Draw(p->GetPosition(), p->GetColour(), m_cameraMatrix);
			}
		}
	}

	// FPS counter
	std::cout << 1 / a_deltaTime << std::endl;
	

	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	//Gizmos::addCylinderFilled(glm::vec3(0.f, 2.f, 0.f), 2.f, 4, 20, glm::vec4(0.4f, 0.2f, 0.6f, 1.f));

	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void MyApplication::onDraw()
{
	
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void MyApplication::onDestroy()
{
	// clean up anything we created
	TextureManager::DestroyInstance();

	//Sets Emitter to null and deletes it
	Emitter1 = nullptr;
	delete Emitter1;

	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	MyApplication* app = new MyApplication();
	
	if (app->create("Test Project",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}