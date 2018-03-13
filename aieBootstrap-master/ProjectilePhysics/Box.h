#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box(glm::vec2 position, glm::vec2 extents, float mass, glm::vec4 colour);
	Box(glm::vec2 position, glm::vec2 extents, float mass, glm::vec2 velocity,
		glm::vec4 colour);
	~Box();

	void makeGizmo();
	bool checkCollision(PhysicsObject*);

	glm::vec2 getExtents() { return m_extents; }
	void setExtents(glm::vec2 extents) { m_extents = extents; }

protected:
	glm::vec2 m_extents;
	glm::vec4 m_colour;
	glm::mat4 m_transform;
};

