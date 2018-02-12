#include "ProjectilePhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Sphere.h"
#include "Plane.h"
#include <imgui.h>

#define M_PI 3.141592654

ProjectilePhysicsApp::ProjectilePhysicsApp() {

}

ProjectilePhysicsApp::~ProjectilePhysicsApp() {

}

bool ProjectilePhysicsApp::startup() {
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setTimeStep(0.01f);
	m_physicsScene->setGravity(glm::vec2(0, -100));

	float radius = 1.f;
	float speed = 25;
	glm::vec2 startPos(-40, 0);
	float angle = (float)M_PI / 4.f;

	auto plane = new Plane({ 0, 1 }, 2);
	auto rSphere = new Sphere(startPos, glm::vec2(speed * 2, speed / 2), angle, 10.f, 2.f, glm::vec4(1, 0, 0.5, 1));
	m_physicsScene->addActor(rSphere);
	m_physicsScene->addActor(new Sphere(startPos, glm::vec2(speed / 5, speed), angle, 1, radius, glm::vec4(1, 0, 0, 1)));
	return true;
}

void ProjectilePhysicsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_physicsScene;
}

void ProjectilePhysicsApp::update(float deltaTime) {

	aie::Gizmos::clear();
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ProjectilePhysicsApp::draw() {

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

void ProjectilePhysicsApp::setupContinuousDemo(glm::vec2 startPos, float angle, float speed, float gravity)
{
	float t = 0.f;
	float tStep = 0.05f;
	float radius = 1.f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	glm::vec2 pos = startPos;
	
	while (t <= 5)
	{		
		//calculate the x, y position of the projectile at time t
		pos += speed * t;
		pos.y += speed * t + gravity * std::pow(t, 2);
		
		aie::Gizmos::add2DCircle(pos, radius, segments, colour);
		t += tStep;
	}
}