#ifndef __BASEENTITY_H
#define __BASEENTITY_H

#include <vector>
#include <string>
#include "IEntity.h"
#include "EntityManager.h"
#include "..\..\common\logger\Logger.h"
#include "..\..\common\utils\HashedString.h"
#include "..\..\engine\gfx\IRenderer.h"

class CollisionPrimitive;

typedef std::vector<IEntity*> ChildrenList;
// BaseEntity Description
//
// An implementation of the IEntity interface. The collidable object
// in BaseEntity will be NULL and therefore, won't be tracked by the
// physics engine.
// Ask the CollidableFactory for a collidable object which will
// register both the entity and the collidable object to the physics
// engine
class BaseEntity : public IEntity
{
public:

	// It's preferable if you set the name of the entity AND it's centre first
	BaseEntity(const std::string &name, const Vector2f &centre);
	virtual ~BaseEntity(void);

	virtual void forward();
	// Don't need them ! 
	//virtual void moveBackward(const Vector2f &vel);
	//virtual void moveLeft(const Vector2f &vel);
	//virtual void moveRight(const Vector2f &vel);
	virtual void fire();
	virtual void update();
	virtual void render(IRenderer *renderer);
	virtual void rotate(float radians);
	void turnLeft();
	void turnRight();

	virtual bool loadVertexList(const char *filename);

	virtual bool isDestroyed();
	virtual void SetExplosionDrawn(bool bSet);
	virtual bool GetExplosionDrawn();
	virtual void setDestroyed(bool d);

	virtual void setVisible(const bool visibility);
	virtual void setColour(const float r, const float g, const float b, const float a);
	virtual void setPosition(const Vector2f &newPos);
	virtual void setAngle(const float angle);
	virtual void setHeading(const Vector2f &newHeading);
	virtual void setMaxSpeed(const float maxspeed);
	virtual void setVelocity(const Vector2f &vel);
	virtual void setCurrentSpeed(const float currentSpeed);
	virtual void setCurrentState(const STATE kState);

	virtual const STATE getCurrentState();	
	virtual const float getCurrentSpeed();	
	virtual const Vector2f getVelocity() const;	
	virtual const float getMaxSpeed() const;	
	virtual const Vector2f getHeading() const;
	virtual const float getAngle() const;
	// i should be Careful with the position, since i am getting the position of the CENTRE of the entity.
	// Which by default will be (0.5,0.5)
	virtual const Vector2f getPosition() const;
	virtual const ColourRGBA getColour() const;
	virtual const bool isVisible() const;
	virtual const std::string getName() const;
	virtual const unsigned int getNumVertices() const;
	virtual const unsigned long getEntityId() const;

	// Need to be careful with this function!!!!
	// No need to delete the pointer because the VectorList is an std::vector
	// and will delete itself
	virtual const VertexList* getVertexListPointer() const;
	virtual CollisionPrimitive* getCollisionPrimitive() const;

	virtual void reset() {}

	virtual IEntity* GetOwner() const { return owner; }
	virtual void SetOwner(IEntity* val) { owner = val; }

	virtual IEntity* GetOwning() const { return owning; }
	virtual void SetOwning(IEntity* val) { owning = val; }

	MathLib::Vector2f GetForce() const { return m_Force; }
	void SetForce(MathLib::Vector2f val) { m_Force = val; }
	void AddForce(MathLib::Vector2f val) { m_Force += val; }
	void ClearForce(){m_Force=Vector2f(0,0);}
	MathLib::Vector2f GetAcceleration() const { return m_Acceleration; }
	void SetAcceleration(MathLib::Vector2f val) { m_Acceleration = val; }
	float GetMass() const { return mass; }
	float GetInverseMass() const { return (float)(1/mass); }
	void SetMass(float val) { mass = val; }

	void addChild(IEntity *pEnt);
protected:
	//// Protected. Entities *must* have valid names!!!
	//BaseEntity();
	bool m_IsDestroyed;

	ColourRGBA m_Colour;
	Vector2f m_Centre;
	HashedString m_EntityIdent;
	bool m_bIsVisible;
	VertexList m_VectorList;
	Matrix44f m_Matrix;

	float m_AngleAcceleration;
	float m_Angle;
	Vector2f m_Acceleration;
	float m_Drag;
	float m_MaxSpeed;
	float mass;

	Vector2f m_Force;
	float m_Speed;	
	Vector2f m_Velocity;
	Vector2f m_Heading;
	STATE m_State;
	bool bExplosionDrawn;

	IEntity* owner;
	IEntity* owning;

	CollisionPrimitive *m_CollisionPrimitive;

	ChildrenList m_Children;
};
inline CollisionPrimitive* BaseEntity::getCollisionPrimitive() const 
{
	return m_CollisionPrimitive;
}

inline void BaseEntity::addChild(IEntity *pEnt)
{
	m_Children.push_back(pEnt);
}
inline void BaseEntity::SetExplosionDrawn(bool bSet)
{
	bExplosionDrawn = bSet;
}
inline bool BaseEntity::GetExplosionDrawn()
{
	return bExplosionDrawn;
}
inline void BaseEntity::setCurrentState(const STATE kState)
{
	m_State = kState;
}

inline const STATE BaseEntity::getCurrentState()
{
	return m_State;
}

inline void BaseEntity::setCurrentSpeed(const float currentSpeed)
{
	m_Speed = currentSpeed;
}
	
inline const float BaseEntity::getCurrentSpeed()
{
	return m_Speed;
}

inline void BaseEntity::setVelocity(const Vector2f &vel)
{
	m_Velocity = vel;
}
inline const Vector2f BaseEntity::getVelocity() const
{
	return m_Velocity;
}

inline bool BaseEntity::isDestroyed()
{
	return m_IsDestroyed;
}
inline void BaseEntity::setDestroyed(bool d)
{
	m_IsDestroyed = d;
	if(d == true)
	{
		bExplosionDrawn = false;
	}
}

inline void BaseEntity::setMaxSpeed(const float maxspeed)
{
	m_MaxSpeed = maxspeed;
}
	
inline const float BaseEntity::getMaxSpeed() const
{
	return m_MaxSpeed;
}

inline const float BaseEntity::getAngle() const 
{
	return m_Angle;
}
inline void BaseEntity::setHeading(const Vector2f &newHeading)
{
	m_Heading = newHeading;
}	
inline const Vector2f BaseEntity::getHeading() const
{
	return m_Heading;
}
inline void BaseEntity::setAngle(const float angle)
{
	m_Angle = angle;
}
inline void BaseEntity::setVisible(const bool visibility)
{
	m_bIsVisible = visibility;

	if(m_CollisionPrimitive != NULL)
		m_CollisionPrimitive->setVisibility(visibility);
}
inline void BaseEntity::setColour(const float r, const float g, const float b, const float a)
{
	m_Colour.r = r;
	m_Colour.g = g;
	m_Colour.b = b;
	m_Colour.a = a;
}
inline void BaseEntity::setPosition(const Vector2f &newPos)
{
	m_Centre = newPos;

	if(m_CollisionPrimitive != NULL)
		m_CollisionPrimitive->Position = newPos;
}
inline const Vector2f BaseEntity::getPosition() const
{
	return m_Centre;
}
inline const ColourRGBA BaseEntity::getColour() const
{
	return m_Colour;
}
inline const bool BaseEntity::isVisible() const
{
	return m_bIsVisible;
}
inline const std::string BaseEntity::getName() const
{
	return m_EntityIdent.getStr();
}
inline const unsigned int BaseEntity::getNumVertices() const
{
	return m_VectorList.size();
}
inline const unsigned long BaseEntity::getEntityId() const
{
	return m_EntityIdent.getHashValue();
}
// Careful with this function!!!!
// No need to delete the pointer because the VectorList is an std::vector
// and will delete itself
inline const VertexList* BaseEntity::getVertexListPointer() const
{
	return &m_VectorList;
}

#endif