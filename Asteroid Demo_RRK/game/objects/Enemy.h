#ifndef __ENEMY_H
#define __ENEMY_H

#include "BaseEntity.h"
#include "..\..\engine\ai\ai_StateMachine.h"
#include "..\..\common\utils\Random.h"
#include "..\physics\CollisionPrimitives.h"
#include "Laser.h"

// Enemy Description
//
// Each enemy is an instance of a vertex list that is loaded by the Entity Manager at start.
// Basically, instead of copying vertex lists for each different enemy for each round (which increases memory), 
// I centralized all the vertex lists in Entity Manager and just overridden the 
// getVertexListPointer() function to point to the current vertex list in the
// Entity Manager. 
// I cheated here because I know that the enemy designs are different for each level so I can
// get away with all the enemies pointing to a "current" vertex list. If it was a real application
// where this isn't a case, I would've used the "getVertexInstancePointer(unsigned int)" function to get a 
// particular vertex list.
class Enemy : public BaseEntity
{
public:

	Enemy(const std::string &name, const Vector2f &centre);
	virtual const VertexList* getVertexListPointer() const;
	virtual ~Enemy(void);

	//Enemy Disappears Suddenly because the acos(angle) gives a small number
	//which gets added to m_angle
	bool RotateHeading(Vector2f target,float val=0.1);

	StateMachine<Enemy>* GetStateMachine() const { return sStateMachine; }
	void SetStateMachine(StateMachine<Enemy>* val) { sStateMachine = val; }

	MathLib::Vector2f GetExitpoint() const { return exitpoint; }
	void SetExitpoint(MathLib::Vector2f val) { exitpoint = val; }

	IEntity* GetTarget() const { return target; }
	void SetTarget(IEntity* val) 
	{
		if(val != NULL)
		{
			std::string s = "Enemy: ";
			s.append(getName());
			s.append(" Assigned target: ");
			s.append(val->getName());
			Logger::GetInstance()->printMsg(INFO, s.c_str());
		}
		target = val; 
	}

	virtual void fire();
	virtual void update();
	virtual void render(IRenderer *renderer);
	virtual void reset();
	void InitState();

private:
	bool fired;
	Laser *laser;
	float maxturnrate;

	StateMachine<Enemy>* sStateMachine;
	IEntity* target;	
	MathLib::Vector2f exitpoint;
	
	Random rng;
};

#endif