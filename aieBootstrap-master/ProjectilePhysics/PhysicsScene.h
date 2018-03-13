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
	void debugScene();

	void setGravity(glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() { return m_gravity; }

	void setTimeStep(float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() { return m_timeStep; }

	std::vector<PhysicsObject*> getActors() { return m_actors; }

	void checkForCollision();
	static bool plane2sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2aabb(PhysicsObject*, PhysicsObject*);
	static bool sphere2plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2aabb(PhysicsObject*, PhysicsObject*);
	static bool aabb2plane(PhysicsObject*, PhysicsObject*);
	static bool aabb2sphere(PhysicsObject*, PhysicsObject*);
	static bool aabb2aabb(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

