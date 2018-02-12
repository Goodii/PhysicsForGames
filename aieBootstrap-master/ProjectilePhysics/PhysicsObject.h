#pragma once
#include <glm/glm.hpp>


class PhysicsObject
{
public:
	enum ShapeType
	{
		PLANE = 0,
		SPHERE,
		BOX,
		SHAPE_COUNT
	};

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
	PhysicsObject() { m_shapeID = SPHERE; }

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	ShapeType getShapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};
