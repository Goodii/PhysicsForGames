#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;

class PhysicsScene
{
public:
	struct CollisionData
	{
		bool wasCollision;
		glm::vec2 normal;
		float overlap;
	};

	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float deltaTime);
	void updateGizmos();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void debugScene();

	void checkForCollision();
	static bool plane2sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2sphere(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

