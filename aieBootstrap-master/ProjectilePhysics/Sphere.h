#pragma once
#include <glm/glm.hpp>
#include "RigidBody.h"

class RigidBody;

class Sphere : public RigidBody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, 
		float linearDrag, float angularDrag, glm::vec4 colour);
	~Sphere();

	virtual void makeGizmo();
	virtual bool checkCollision(PhysicsObject* pOther);

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

	void drawLine(glm::vec2 originalPosition);

protected: 
	float m_radius; 
	glm::vec4 m_colour;
};

