#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Box.h"

class ProjectilePhysicsApp : public aie::Application {
public:

	ProjectilePhysicsApp();
	virtual ~ProjectilePhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:

	Box* box;
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* m_physicsScene;
};