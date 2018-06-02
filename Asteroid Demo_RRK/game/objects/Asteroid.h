#ifndef __Asteroid_H
#define __Asteroid_H

#include "baseentity.h"
#include "..\..\engine\gfx\GraphicsManager.h"
#include "..\physics\CollisionPrimitives.h"
#include "..\..\engine\ai\ai_StateMachine.h"

class Asteroid :	public BaseEntity
{
public:

	Asteroid(const std::string &name, const Vector2f &centre);
	virtual void render(IRenderer *renderer);
	virtual void update();
	virtual ~Asteroid();
	//virtual const VertexList* getVertexListPointer() const;
	virtual void reset();

private:
	virtual void fire() {};
	virtual void rotate(float radians) {};
	virtual void turnLeft() {};
	virtual void turnRight() {};
	// Not Sure if i need this but any way lets see...
	//StateMachine<Asteroid>* sStateMachine;

};

#endif