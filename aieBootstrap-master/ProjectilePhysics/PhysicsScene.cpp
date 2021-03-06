#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <algorithm>
#include <list>
#include "RigidBody.h"
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include <vector>
#include <Gizmos.h>

//delete before submission
#include <Input.h>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto& pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::update(float deltaTime)
{
	//update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		checkForCollision();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	assert(actor != nullptr);
	assert(std::find(std::begin(m_actors), std::end(m_actors), actor) == m_actors.end());
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{	
	std::remove(std::begin(m_actors), std::end(m_actors), actor);	
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->debug();
		count++;
		
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	nullptr,	PhysicsScene::plane2sphere, PhysicsScene::plane2aabb,
	PhysicsScene::sphere2plane, PhysicsScene::sphere2sphere, PhysicsScene::sphere2aabb,
	PhysicsScene::aabb2plane, PhysicsScene::aabb2sphere, PhysicsScene::aabb2aabb,
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	//need to check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();
			
			//using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::plane2sphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane = dynamic_cast<Plane*>(object1);
	Sphere* sphere = dynamic_cast<Sphere*>(object2);
	assert(sphere && plane);

	glm::vec2 collisionNormal = plane->getNormal();
	float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

	if (sphereToPlane < 0)
	{
		collisionNormal *= -1;
		sphereToPlane *= -1;
	}

	float intersection = sphere->getRadius() - sphereToPlane;
	if (intersection > 0)
	{
		//pushes sphere away from plane to avoid merging
		glm::vec2 repulsiveForce = glm::vec2(collisionNormal * sphereToPlane);
		sphere->applyForce(-repulsiveForce);

		//applies force to sphere
		plane->resolveCollision(sphere);
		return true;
	}
	return false;
}

bool PhysicsScene::sphere2plane(PhysicsObject* object1, PhysicsObject* object2)
{
	return plane2sphere(object2, object1);
}

bool PhysicsScene::sphere2sphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);
	assert(sphere1 && sphere2);

	float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
	float radius = sphere1->getRadius() + sphere2->getRadius();

	glm::vec2 normal = glm::normalize(sphere1->getPosition() - sphere2->getPosition());
	
	if (distance < radius)
	{
		sphere1->resolveCollision(sphere2);

		return true;
	}
	
	return false;
}

bool PhysicsScene::plane2aabb(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane = dynamic_cast<Plane*>(object1);
	Box* box = dynamic_cast<Box*>(object2);
	assert(box && plane);

	glm::vec2 collisionNormal = plane->getNormal();
	float aabbToPlane = glm::dot(box->getPosition(), plane->getNormal() - plane->getDistance());

	float r = box->getExtents().x * abs(plane->getNormal().x) + box->getExtents().y * abs(plane->getNormal().y);
	float s = glm::dot(plane->getNormal(), box->getPosition()) - plane->getDistance();
	
	if (aabbToPlane < 0)
	{
		collisionNormal *= -1;
		aabbToPlane *= -1;
	}

	//check intersection between plane and aabb
	glm::vec2 intersection = glm::vec2(box->getExtents().x - aabbToPlane, box->getExtents().y - aabbToPlane);
	
	if (abs(s) <= r)
	{
		glm::vec2 repulsiveForce = glm::vec2(collisionNormal * abs(s));
		box->applyForce(-repulsiveForce);
		plane->resolveCollision(box);
		return true;
	}

	return false;
}

bool PhysicsScene::sphere2aabb(PhysicsObject* object1, PhysicsObject* object2)
{
	return aabb2sphere(object2, object1);
}

bool PhysicsScene::aabb2plane(PhysicsObject* object1, PhysicsObject* object2)
{
	return plane2aabb(object2, object1);
}

bool PhysicsScene::aabb2sphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Box* box = dynamic_cast<Box*>(object1);
	Sphere* sphere = dynamic_cast<Sphere*>(object2);
	assert(box && sphere);
	
	//clamp
	glm::vec2 clamped = glm::clamp(sphere->getPosition(), box->getMin(), box->getMax());
	//get vecbetween (position - clamp position)
	glm::vec2 vecBetween = sphere->getPosition() - clamped;

	aie::Gizmos::add2DCircle(clamped, 0.5f, 12, { 1, 0, 0, 1 });

	float distanceSquared = glm::length(vecBetween * vecBetween);
	float radiusSquared = sphere->getRadius() * sphere->getRadius();

	//get normal
	if (clamped.x != 0 && clamped.y != 0)
	{
		glm::vec2 normal = glm::normalize(sphere->getPosition() - clamped);
		//resolve collision
		if (distanceSquared < radiusSquared)
		{
			box->resolveCollision(sphere, normal);
			std::cout << "AABB vs Sphere collision detected\n";
			return true;
		}
	}
	return false;
}

bool PhysicsScene::aabb2aabb(PhysicsObject* object1, PhysicsObject* object2)
{
	Box* box1 = dynamic_cast<Box*>(object1);
	Box* box2 = dynamic_cast<Box*>(object2);
	assert(box1 && box2);

	if ((box1->getMin().x <= box2->getMax().x && box1->getMax().x >= box2->getMin().x) &&
		(box1->getMin().y <= box2->getMax().y && box1->getMax().y >= box2->getMin().y))
	{
		box2->resolveCollision(box1);
		std::cout << "Box vs Box collision detected\n";

		return true;
	}

	return false;
}
