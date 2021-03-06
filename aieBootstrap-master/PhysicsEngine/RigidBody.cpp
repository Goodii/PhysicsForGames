#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID)
{
	m_shapeID = shapeID;
}

RigidBody::RigidBody(glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(m_shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
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
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

