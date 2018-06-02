#ifndef __IENTITY_H
#define __IENTITY_H

#include <vector>
#include "..\..\game\physics\CollisionPrimitives.h"
#include "..\..\common\utils\Mathlib.h"
#include "..\..\common\utils\ColourRGBA.h"
#include "..\..\Engine\engine.h"

using namespace MathLib;

class IRenderer;
class PhysCollidable;

typedef std::vector<Vector2f> VertexList;

static const enum STATE
{
	ALIVE,
	DEAD,
	SPAWNING
};

// might need to think what to put here too
class IEntity
{
public:
	virtual ~IEntity() {};

	virtual void forward() = 0;
	virtual void fire() = 0;
	virtual void rotate(float radians) = 0;
	virtual void turnLeft() = 0;
	virtual void turnRight() = 0;

	virtual bool isDestroyed() = 0;
	virtual bool loadVertexList(const char *filename) = 0;
	virtual void setDestroyed(bool d) = 0;

	virtual void SetExplosionDrawn(bool bSet) =0;
	virtual bool GetExplosionDrawn() =0;

	//virtual void setName(const std::string newName) = 0;
	virtual void setVisible(const bool visibility) = 0;
	virtual void setColour(const float r, const float g, const float b, const float a) = 0;
	virtual void setPosition(const Vector2f &newPos) = 0;
	virtual void setAngle(const float angle) = 0;
	virtual void setHeading(const Vector2f &newHeading) = 0;
	virtual void setMaxSpeed(const float maxspeed) = 0;
	virtual void setVelocity(const Vector2f &vel) = 0;
	virtual void setCurrentSpeed(const float currentSpeed) = 0;
	virtual void setCurrentState(const STATE kState) = 0;

	virtual const STATE getCurrentState() = 0;
	virtual const float getCurrentSpeed() = 0;
	virtual const Vector2f getVelocity() const = 0;
	virtual const float getMaxSpeed() const = 0;
	virtual const Vector2f getHeading() const = 0;
	virtual const float getAngle() const = 0;
	virtual const Vector2f getPosition() const = 0;
	virtual const ColourRGBA getColour() const = 0;
	virtual const bool isVisible() const = 0;
	virtual const std::string getName() const = 0;
	virtual const unsigned int getNumVertices() const = 0;
	virtual const unsigned long getEntityId() const = 0;
	virtual const VertexList* getVertexListPointer() const = 0;
	virtual CollisionPrimitive* getCollisionPrimitive() const = 0;

	// Updates the transformation matrices
	// and any other updates needed for the entity
	virtual void render(IRenderer *renderer) = 0;
	virtual void update() = 0;
	virtual void reset() = 0;

	virtual IEntity* GetOwner() const = 0;
	virtual void SetOwner(IEntity* val) = 0;

	virtual IEntity* GetOwning() const = 0;
	virtual void SetOwning(IEntity* val) = 0;

	virtual MathLib::Vector2f GetForce() const = 0;
	virtual void SetForce(MathLib::Vector2f val) = 0;
	virtual void AddForce(MathLib::Vector2f val) = 0;
	virtual void ClearForce() = 0;
	virtual MathLib::Vector2f GetAcceleration() const = 0;
	virtual void SetAcceleration(MathLib::Vector2f val) = 0;
	virtual float GetMass() const = 0;
	virtual float GetInverseMass() const = 0;
	virtual void SetMass(float val) = 0;

	virtual void addChild(IEntity *pEnt) = 0;
};

#endif