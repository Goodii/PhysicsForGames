#include "Plane.h"
#include <Gizmos.h>

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	m_normal = normal;
	m_distanceToOrigin = distance;
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centre = m_normal * m_distanceToOrigin;
	
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centre + (parallel * lineSegmentLength);
	glm::vec2 end = centre - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resolveCollision(RigidBody* actor2)
{
	glm::vec2 relativeVelocity = actor2->getVelocity();
	
	float j = glm::dot(-(1 + actor2->getElasticity()) * (relativeVelocity), m_normal) / (1 / actor2->getMass());

	glm::vec2 force = m_normal * j;

	actor2->applyForce(force);
}