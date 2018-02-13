#pragma once
#include "RigidBody.h"

class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 normal, float distance);

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) override {}
	virtual void debug() override {}
	void makeGizmo() override;
	virtual void resetPosition() {}

	glm::vec2 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
};

