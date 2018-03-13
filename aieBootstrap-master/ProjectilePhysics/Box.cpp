#include "Box.h"
#include <Gizmos.h>


Box::Box(glm::vec2 position, glm::vec2 extents, float mass, 
		glm::vec4 colour) : RigidBody(AABB, position, glm::vec2(0, 0), 0, mass)
{
	m_extents = extents;
	m_min = glm::vec2(position.x - extents.x / 2, position.y - extents.y / 2);
	m_max = glm::vec2(position.x + extents.x / 2, position.y + extents.y / 2);
	m_colour = colour;
	m_angularDrag = 0;
	m_linearDrag = 0;
}

Box::Box(glm::vec2 position, glm::vec2 extents, float mass, glm::vec2 velocity,
		glm::vec4 colour) : RigidBody(AABB, position, velocity, 0, mass)
{
	m_extents = extents;
	m_min = glm::vec2(position.x - extents.x / 2, position.y - extents.y / 2);
	m_max = glm::vec2(position.x + extents.x / 2, position.y + extents.y / 2);
	m_colour = colour;
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABB(m_position, m_extents, m_colour);
}
void Box::setExtents(glm::vec2 extents)
{
	m_extents = extents;
	m_min = glm::vec2(m_position.x - extents.x / 2, m_position.y - extents.y / 2);
	m_max = glm::vec2(m_position.x + extents.x / 2, m_position.y + extents.y / 2);
}

