#pragma once

#include "CollisionPrimitives.h"
#include "..\..\common\utils\MathLib.h"

using namespace MathLib;

class CollisionDetector
{
public:
	static bool circleAndCircle(const CollisionCircle &c1, const CollisionCircle &c2);
	static bool circleAndLine(const CollisionCircle &circ, const CollisionLine &line);
};