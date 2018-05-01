#include "Sphere.h"
#include <Gizmos.h>


Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, 
				glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_linearDrag = 0.7f;
	m_angularDrag = 0.7f;
}

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius,
				float linearDrag, float angularDrag, 
				glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
}

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius,
				float linearDrag, float angularDrag, float elasticity, 
				glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_elasticity = elasticity;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);

}

void Sphere::drawLine(glm::vec2 originalPosition)
{
	aie::Gizmos::add2DLine(originalPosition, m_position, m_colour);

	originalPosition = m_position;
}
