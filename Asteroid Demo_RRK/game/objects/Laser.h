#ifndef __LASER_H
#define __LASER_H

#include "baseentity.h"
#include "..\physics\CollisionPrimitives.h"
#include "..\GameConstants.h"

class Laser : public BaseEntity
{
public:
	Laser(const Vector2f &startPt, const Vector2f &endPt);
	~Laser(void);

	virtual void setPosition(const Vector2f &newPos);
	virtual void setAngle(const float angle);
	virtual void update();
	virtual void render(IRenderer *renderer);

private:
	virtual void fire() {};
	virtual void rotate(float radians) {};
	virtual void turnLeft() {};
	virtual void turnRight() {};

private:
	Vector2f m_CurrStartPt;
	Vector2f m_CurrEndPt;

	Matrix44f m_RotMtx;

	float m[16];
 };

#endif