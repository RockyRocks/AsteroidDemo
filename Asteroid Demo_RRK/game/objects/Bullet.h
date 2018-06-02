#ifndef __BULLET_H
#define __BULLET_H

#include "baseentity.h"
#include "..\physics\CollisionPrimitives.h"

// Bullet Description
//
// A bullet is basically a small line with a very small radius (for it's collidable)
// It will have 0 drag and will go at a constant speed
class Bullet :	public BaseEntity
{
public:
	Bullet(const std::string &name, const Vector2f &centre);
	virtual ~Bullet();

	virtual void update();

private:
	virtual void fire() {};
	virtual void rotate(float radians) {};
	virtual void turnLeft() {};
	virtual void turnRight() {};
};

#endif