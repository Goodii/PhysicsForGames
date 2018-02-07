#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Sphere.h"

PhysicsEngineApp::PhysicsEngineApp() {

}

PhysicsEngineApp::~PhysicsEngineApp() {

}

bool PhysicsEngineApp::startup() {
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10.f));
	m_physicsScene->setTimeStep(0.01f);

	Sphere* ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 5.f, 4.f, glm::vec4(1, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), 5.f, 4.f, glm::vec4(0, 1, 0, 1));

	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);

	//ball1->applyForceToActor(ball2, glm::vec2(2, 0));

	ball1->applyForce(glm::vec2(30, 150));
	ball2->applyForce(glm::vec2(-31, 148));

	return true;
}

void PhysicsEngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_physicsScene;
}

void PhysicsEngineApp::update(float deltaTime) {
	aie::Gizmos::clear();

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();
	
	//static const glm::vec4 colours[] = {glm::vec4(1,0,0,1), glm::vec4(0,1,0,1), glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1), glm::vec4(0,1,1,1) };
	//
	//static const int rows = 5;
	//static const int columns = 10;
	//static const int hSpace = 1;
	//static const int vSpace = 1;
	//
	//static const glm::vec2 scrExtents(100, 50); 
	//static const glm::vec2 boxExtents(7, 3); 
	//static const glm::vec2 startPos(-(columns >> 1)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f), 
	//								scrExtents.y - ((boxExtents.y * 2) + hSpace));
	//
	////draw grid of blocks
	//glm::vec2 pos;
	//for (int y = 0; y < rows; y++)
	//{
	//	pos = glm::vec2(startPos.x, startPos.y - (y * ((boxExtents.y * 2) + hSpace)));
	//
	//	for (int x = 0; x < columns; x++) 
	//	{ 
	//		aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]); 
	//		pos.x += (boxExtents.x * 2) + vSpace; 
	//	}
	//}
	//
	////draw a ball
	//aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3.f, 12, glm::vec4(1, 1, 0, 1));
	//	
	////draw player
	//aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2), glm::vec4(1, 0, 1, 1));
	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	//gizmos draw
	float aspectRatio = (float)getWindowWidth() / getWindowHeight();
	aie::Gizmos::draw2D(glm::ortho<float>(-100.f, 100.f, 
										-100.f / aspectRatio, 100.f / aspectRatio, 
										-1.f, 1.f));

	// done drawing sprites
	m_2dRenderer->end();
}