#pragma once

#include "..\..\common\utils\MathLib.h"

using namespace MathLib;

static const enum PrimitiveType
{
	NO_TYPE,
	CIRCLE_TYPE,
	LINE_TYPE
};

// CollisionPrimitive
class CollisionPrimitive
{
public:
	CollisionPrimitive() : m_Visible(true){ m_PrimitiveType = NO_TYPE; }

	virtual void setVisibility(bool vis) { m_Visible = vis; }
	virtual bool isVisible() { return m_Visible; }

	virtual PrimitiveType getType() { return m_PrimitiveType; }
protected:
	PrimitiveType m_PrimitiveType;
	bool m_Visible;

public:
	Vector2f Position;
};

// CollisionCircle
class CollisionCircle : public CollisionPrimitive
{
public:
	CollisionCircle(float radius) : CollisionPrimitive(), Radius(radius) { m_PrimitiveType = CIRCLE_TYPE; }

public:
	float Radius;
};

// CollisionLine
class CollisionLine : public CollisionPrimitive
{
public:
	CollisionLine(Vector2f &startpt, Vector2f &endpt) 
		: CollisionPrimitive(), StartPoint(startpt), EndPoint(EndPoint) { m_PrimitiveType = LINE_TYPE; }

public:
	Vector2f StartPoint;
	Vector2f EndPoint;
};