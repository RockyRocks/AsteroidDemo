#include "CollisionDetector.h"

bool CollisionDetector::circleAndCircle(const CollisionCircle &c1, const CollisionCircle &c2)
{
	Vector2f distance = c2.Position - c1.Position;

	float distSquared = distance.dot(distance);
	float radiusSum = c1.Radius + c2.Radius;
	float radiiSquared = radiusSum*radiusSum;
	// perform the test in squared space (removes the need for a square root)
	if(distSquared <= radiiSquared)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionDetector::circleAndLine(const CollisionCircle &circ, const CollisionLine &line)
{
	// Intersection of line and circle from
	// http://local.wasp.uwa.edu.au/~pbourke/geometry/sphereline/
	//
	// Instead of using "mu", I've used "t" and clamped t in the range [0-1] because the line is FINITE.
	// The equations above is intersection with an infinite line, in other words, a ray.
	Vector2f c = circ.Position;
	Vector2f p1 = line.StartPoint;
	Vector2f p2 = line.EndPoint;
	//Vector2f sc = collidable1->getPosition();
	float r = circ.Radius;
 
	Vector2f dir = p2 - p1;
	Vector2f diff = c - p1;
	
	float t = diff.dot(dir) / dir.dot(dir);

	if(t < 0.0f)
		t = 0.0f;
	if(t > 1.0f)
		t = 1.0f;

	// Use distance squared space, avoids using sqrt function.
	Vector2f closest = p1 + t * dir;
	Vector2f d = c - closest;

	float distSquared = d.dot(d);

	return (distSquared <= (r*r));
}