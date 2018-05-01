#include "Box.h"
#include <Gizmos.h>


Box::Box(glm::vec2 position, glm::vec2 extents, float mass, 
		glm::vec4 colour) : RigidBody(AABB, position, glm::vec2(0, 0), 0, mass)
{
	setExtents(extents);
	m_colour = colour;
	m_angularDrag = 0;
	m_linearDrag = 0;
}

Box::Box(glm::vec2 position, glm::vec2 extents, float mass, glm::vec2 velocity,
		glm::vec4 colour) : RigidBody(AABB, position, velocity, 0, mass)
{
	setExtents(extents);
	m_colour = colour;
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABB(m_position, m_extents, m_colour);
	aie::Gizmos::add2DCircle(getMin(), 1, 12, m_colour);
	aie::Gizmos::add2DCircle(getMax(), 1, 12, m_colour);
}

void Box::setExtents(glm::vec2 extents)
{
	m_extents = extents;
	m_halfExtents = m_extents * 0.5f;
	m_min = m_position - m_halfExtents;
	m_max = m_position + m_halfExtents;
}

glm::vec2 Box::getMin()
{
	return m_position - m_extents;
}

glm::vec2 Box::getMax()
{
	return m_position + m_extents;
}

