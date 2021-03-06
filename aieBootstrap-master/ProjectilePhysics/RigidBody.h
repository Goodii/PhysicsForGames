#pragma once
#include <glm/glm.hpp>
#include "PhysicsObject.h"

class PhysicsObject;

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, 
		float rotation, float mass);
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity,
		float rotation, float mass, float elasticity);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() override { };
	void applyForce(glm::vec2 force);
	void applyForceToActor(RigidBody* actor2, glm::vec2 force);

	void resolveCollision(RigidBody* actor2);
	void resolveCollision(RigidBody* actor2, glm::vec2 normal);

	glm::vec2 getPosition() { return m_position; }
	void setPosition(glm::vec2 position) { m_position = position; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec2 newVelocity) { m_velocity = newVelocity; }
	float getLinearDrag() { return m_linearDrag; }
	void setLinearDrag(float linearDrag) { m_linearDrag = linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	void setAngularDrag(float angularDrag) { m_angularDrag = angularDrag; }
	float getMass() { return m_mass; }
	float getElasticity() { return m_elasticity; }
	void setElasticity(float elasticity) { m_elasticity = elasticity; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;
	float m_elasticity;
	float m_angularVelocity;
	float m_linearDrag;
	float m_angularDrag;
};

