#include "Sphere.h"
#include <Gizmos.h>


Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float angle,
				float mass, float radius, glm::vec4 colour)
				: RigidBody(position, 
					velocity, angle, mass)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
}

bool Sphere::checkCollision(PhysicsObject* pOther)
{
	Sphere* other = dynamic_cast<Sphere*>(pOther);	
	
	float distance = glm::distance(getPosition(), other->getPosition());

	if (distance < getRadius() + other->getRadius())
	{
		return true;
	}

	return false;
}
