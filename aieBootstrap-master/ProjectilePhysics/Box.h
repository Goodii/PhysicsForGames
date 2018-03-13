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

	glm::vec2 getExtents() { return m_extents; }
	void setExtents(glm::vec2 extents);
	glm::vec2 getMin() { return m_min; }
	glm::vec2 getMax() { return m_max; }

protected:
	glm::vec2 m_extents;
	glm::vec2 m_min;
	glm::vec2 m_max;
	glm::vec4 m_colour;
	glm::mat4 m_transform;
};

