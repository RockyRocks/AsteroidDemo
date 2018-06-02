#ifndef __ENEMYSTATES_H
#define __ENEMYSTATES_H

#include "..\..\common\logger\Logger.h"
#include "AIEngine.h"
#include "ai_State.h"
#include "..\..\game\objects\Enemy.h"
#include "../../game/objects/BaseEntity.h"
#include "..\sound\SoundManager.h"

// TODO: Make some asteroids into collectibles and add power ups to players who destroys that enemy ship.
class SeekAsteroid : public State<Enemy> 
{
private:
	 	SeekAsteroid(){}
	 	SeekAsteroid(const SeekAsteroid&);
	 	SeekAsteroid& operator=(const SeekAsteroid&);
public:
	static SeekAsteroid* Instance();

	virtual void Enter(Enemy* enemy);

	virtual void Execute(Enemy* enemy);

	virtual void Exit(Enemy* enemy);

	~SeekAsteroid();

};

class FetchAsteroid : public State<Enemy> 
{
private:
	FetchAsteroid(){}
	FetchAsteroid(const FetchAsteroid&);
	FetchAsteroid& operator=(const FetchAsteroid&);
public:
	static FetchAsteroid* Instance();

	virtual void Enter(Enemy* enemy);

	virtual void Execute(Enemy* enemy);

	virtual void Exit(Enemy* enemy);
	
	~FetchAsteroid();
};

class AttackPlayer : public State<Enemy> 
{
private:
	AttackPlayer(){}
	AttackPlayer(const AttackPlayer&);
	AttackPlayer& operator=(const AttackPlayer&);
public:
	static AttackPlayer* Instance();

	virtual void Enter(Enemy* enemy);

	virtual void Execute(Enemy* enemy);

	virtual void Exit(Enemy* enemy);

	~AttackPlayer();
};

#endif