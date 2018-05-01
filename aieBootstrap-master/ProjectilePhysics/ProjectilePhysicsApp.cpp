#include "ProjectilePhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Sphere.h"
#include "Plane.h"
#include "PhysicsObject.h"
#include "Box.h"
#include <imgui.h>

//DELETE FOR SUBMISSION
//right click project -> properties -> general -> platform toolset -> change to 2017 -> clean -> rebuild

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
	m_physicsScene->setGravity(glm::vec2(0.f, -9.8f));


	float angle = (float)M_PI / 4.f;

	auto floor = new Plane({ 0, 1 }, -50);
	m_physicsScene->addActor(floor);
	auto roof = new Plane({ 0, 1 }, 50);
	m_physicsScene->addActor(roof);
	auto wallRight = new Plane({ 1, 0 }, 80);
	m_physicsScene->addActor(wallRight);
	auto wallLeft = new Plane({ 1, 0 }, -80);
	m_physicsScene->addActor(wallLeft);

	box = new Box({ 0, -30 }, { 10, 10 }, 10.f, { 0, 40 }, { 0, 1, 0, 1 });
	m_physicsScene->addActor(box);
	auto box2 = new Box({ 0, 0 }, { 5, 10 }, 20.f, { 0, 15 }, { 0, 1, 0, 1 });
	//m_physicsScene->addActor(box2);
	auto rSphere = new Sphere({ 0, 0 }, glm::vec2(0, -15), 10.f, 5.f, glm::vec4(1, 0, 0.5, 1));
	//m_physicsScene->addActor(rSphere);

	//auto eSphere = new Sphere({ 0, -45 }, glm::vec2(0, 50), 1.f, 3.f, glm::vec4(1, 0, 0.5, 1));
	//m_physicsScene->addActor(eSphere);

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

	float weight = rand() % 14 + 5;

	//generate random colour
	glm::vec4 randomRGB = glm::vec4((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), 1.f);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{				
		m_physicsScene->addActor(new Sphere(glm::vec2(0, 30), glm::vec2(-20, 0), weight, 0.35 * weight, randomRGB));
	}

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_physicsScene->addActor(new Sphere(glm::vec2(0, 30), glm::vec2(0, -10), weight, 0.35f * weight, randomRGB));
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		box->applyForce({ 30, 0 });
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		box->applyForce({ -30, 0 });
	}
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		box->applyForce({ 0, 30 });
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		box->applyForce({ 0, -30 });
	}

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

	aie::Gizmos::add2DLine({ 100, 0 }, { -100, 0 }, { 0.2f, 0.2f, 0.2f, 1 });
	aie::Gizmos::add2DLine({ 0, 100 }, { 0, -100 }, { 0.2f, 0.2f, 0.2f, 1 });

	//gizmos draw
	float aspectRatio = (float)getWindowWidth() / getWindowHeight();
	aie::Gizmos::draw2D(glm::ortho<float>(-100.f, 100.f,
		-100.f / aspectRatio, 100.f / aspectRatio,
		-1.f, 1.f));

	// done drawing sprites
	m_2dRenderer->end();
}
