#include "RigidBody.h"

#define MIN_LINEAR_THRESHOLD 0.1f
#define MIN_ROTATION_THRESHOLD 0.01f

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, 
	float rotation, float mass) : PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_linearDrag = 0.3f;
	m_angularDrag = 0.3f;
	m_elasticity = 0.9f;
}

RigidBody::~RigidBody()
{
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody* actor2, glm::vec2 force)
{
	actor2->applyForce(force);

	applyForce(-(force));
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	
	if (m_velocity.length() < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec2(0, 0);
	}

	if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = 0;
	}

	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

void RigidBody::resolveCollision(RigidBody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
	
	float j = glm::dot(-(1 + getElasticity()) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;
	
	applyForceToActor(actor2, force);
}


