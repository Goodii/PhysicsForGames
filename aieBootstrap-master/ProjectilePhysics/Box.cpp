#include "Box.h"
#include <Gizmos.h>


Box::Box(glm::vec2 position, glm::vec2 extents, float mass, 
		glm::vec4 colour) : RigidBody(AABB, position, glm::vec2(0, 0), 0, mass)
{
	m_extents = extents;
	m_colour = colour;
}

Box::Box(glm::vec2 position, glm::vec2 extents, float mass, glm::vec2 velocity,
		glm::vec4 colour) : RigidBody(AABB, position, velocity, 0, mass)
{
	m_extents = extents;
	m_colour = colour;
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, m_extents, m_colour, &m_transform);
}

bool Box::checkCollision(PhysicsObject* pOther)
{
	Box* other = dynamic_cast<Box*>(pOther);

	float distance = glm::distance(getPosition(), other->getPosition());

	return false;
}


