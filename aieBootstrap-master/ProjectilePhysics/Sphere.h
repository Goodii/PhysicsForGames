#pragma once
#include <glm/glm.hpp>
#include "RigidBody.h"

class RigidBody;

class Sphere : public RigidBody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float angle, float mass, float radius, glm::vec4 colour);
	~Sphere();

	virtual void makeGizmo();
	virtual bool checkCollision(PhysicsObject* pOther);

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected: 
	float m_radius; 
	glm::vec4 m_colour;
};

