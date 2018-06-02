#include "ai_EnemyStates.h"

// TODO: Make some asteroids into collectibles and add power ups to players who destroys that enemy ship.

SeekAsteroid* SeekAsteroid::Instance()
{
	static SeekAsteroid ob;
 	return &ob;
}

void SeekAsteroid::Enter( Enemy* enemy )
{
	// Ask the AI Engine for a random target
	const TargetList* pTargets= AIEngine::GetInstance()->getTargetList();
	
	int nfules=pTargets->size();
	enemy->SetTarget(NULL);
	IEntity* target=enemy->GetTarget();
	for(int i=0;i<nfules;i++)
	{	
		// only assign targets if they don't have an owner and if they are in play (visible)
		if(pTargets->at(i)->GetOwner()==NULL && pTargets->at(i)->isVisible() == true)
		{
			float prevdistance=1,nowdistance=0;
				if(target)
					prevdistance=(target->getPosition()-enemy->getPosition()).length();

				nowdistance=(pTargets->at(i)->getPosition()-enemy->getPosition()).length();

			if(nowdistance<prevdistance || target==NULL)
			{
				if(target)
					target->SetOwner(NULL);

				target=pTargets->at(i);
				pTargets->at(i)->SetOwner(enemy);
				enemy->SetOwning(pTargets->at(i));
			}
		}
	}

	if(target==NULL)
	{
		enemy->GetStateMachine()->ChangeState(AttackPlayer::Instance());
		return;
	}
	enemy->SetTarget(target);
}

void SeekAsteroid::Execute( Enemy* enemy )
{
	IEntity* target=enemy->GetTarget();
	//If not aligned With Asteroid , return
	enemy->RotateHeading(target->getPosition());

	Vector2f dir = enemy->getPosition() - target->getPosition();

	Vector2f dirofforce=enemy->getPosition()-target->getPosition();
	float length=dirofforce.length();
	dirofforce.normalise();
	
	enemy->AddForce(dirofforce*-length*2);
	
	if(length < 50)
		enemy->GetStateMachine()->ChangeState(FetchAsteroid::Instance());

}

void SeekAsteroid::Exit( Enemy* enemy )
{
}

SeekAsteroid::~SeekAsteroid()
{

}


FetchAsteroid* FetchAsteroid::Instance()
{
	static FetchAsteroid ob;
	return &ob;
}

void FetchAsteroid::Enter( Enemy* enemy )
{
	enemy->SetExitpoint(enemy->getHeading()*-1000);
	IEntity* target=enemy->GetTarget();	
	target->setMaxSpeed(enemy->getMaxSpeed());
	//target->setMaxSpeed(3.0f);

}
// TODO: Need to look into this once properly !
void FetchAsteroid::Execute( Enemy* enemy )
{
	if (!enemy->RotateHeading(enemy->GetExitpoint(),0.6))
		return;

	Vector2f currentdistance=enemy->getPosition()-enemy->GetExitpoint();
	if(currentdistance.length()<50 && enemy->getCurrentState() == ALIVE)
	{
		enemy->SetOwning(NULL);	
		enemy->GetStateMachine()->ChangeState(SeekAsteroid::Instance());
	}

	IEntity* target = enemy->GetTarget();
	enemy->AddForce(enemy->getHeading()*200);
	//target->AddForce(enemy->GetForce());
	target->AddForce(enemy->getHeading()*200);
}

void FetchAsteroid::Exit( Enemy* enemy )
{
#ifdef _DEBUG
	std::string s = "Enemy: ";
	s.append(enemy->getName());
	s.append(" exiting fetch Asteroid state");
	Logger::GetInstance()->printMsg(INFO, s.c_str());
#endif
	if(enemy->getCurrentState() == ALIVE)
	{
		//enemy->GetStateMachine()->ChangeState(SeekAsteroid::Instance());
	}

}

FetchAsteroid::~FetchAsteroid()
{

}

AttackPlayer* AttackPlayer::Instance()
{
static AttackPlayer instance;
return &instance;
}

void AttackPlayer::Enter( Enemy* enemy )
{
#ifdef _DEBUG
	Logger::GetInstance()->printMsg(INFO, "Enter AttackingPlayer");
#endif
	IEntity *player = AIEngine::GetInstance()->getRandomPlayer();
	enemy->SetTarget(player);
}

void AttackPlayer::Execute( Enemy* enemy )
{
	IEntity* target=enemy->GetTarget();
	//If not aligned With Asteroid , return
	enemy->RotateHeading(target->getPosition());

	Vector2f dirofforce=enemy->getPosition()-target->getPosition();
	float length=dirofforce.length();

	dirofforce.normalise();
	enemy->AddForce(dirofforce*-length);
	
	enemy->fire();	
}

void AttackPlayer::Exit( Enemy* enemy )
{

}

AttackPlayer::~AttackPlayer()
{

}