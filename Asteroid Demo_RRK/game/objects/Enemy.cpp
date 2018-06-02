#include "Enemy.h"
#include "..\..\engine\ai\ai_EnemyStates.h"

static const float MAX_FIRE_TIME = 3.0f;

float g_Count;

Enemy::Enemy(const std::string &name, const Vector2f &centre)
: BaseEntity(name, centre)
{
	g_Count = 3.0f;

	laser = NULL;
	fired = false;

	m_Matrix.identity();

	maxturnrate=212.5;

	m_Colour.r = 0.0f;
	m_Colour.g = 1.0f;
	m_Colour.b = 1.0f;
	m_Colour.a = 1.0f;

	m_CollisionPrimitive = new CollisionCircle(10.0f);
	m_CollisionPrimitive->Position = m_Centre;
	setVisible(true);

	// register this entity with the entity manager
	EntityManager::GetInstance()->registerEntity(this);

	sStateMachine=new StateMachine<Enemy>(this);
}

Enemy::~Enemy(void)
{
	//delete laser;
	delete sStateMachine;
}

const VertexList* Enemy::getVertexListPointer() const
{
	return EntityManager::GetInstance()->getCurrentVertexInstancePointer();
}

bool Enemy::RotateHeading(Vector2f target,float val)
{	
	Vector2f dirtotarget=target-m_Centre;
	dirtotarget.normalise();

	float angle=acos(m_Heading.dot(dirtotarget));
//	std::cout<<angle<<"\n";
	if(angle<val)
		return true;

	if(angle>maxturnrate)
		angle=maxturnrate;
	
	//ClockWise or Anti-ClockWise
	int sign=1;
	if(m_Heading.y*dirtotarget.x<m_Heading.x*dirtotarget.y)
		sign=-1;
	
	//Update TotalAngle
	m_Angle-=angle*sign;   //?? Works ?
	m_Matrix.rotate(Vector3f(0,0,1),angle*sign); //Rotate in Z axis
	//Update Heading
	m_Heading=m_Heading*m_Matrix;
	
	return false;
}

void Enemy::fire()
{
	// only fire at certain intervals
	if(!fired)
	{
		laser->setVisible(true);
		fired = true;
		
		Engine::GetInstance()->getSoundSystem()->play(7);
	}
}

void Enemy::update()
{
	if(laser == NULL)
		laser = (Laser*) m_Children.at(0);

	// only update the enemy & ai if it's alive
	if(m_State == ALIVE)
	{
		BaseEntity::update();

		sStateMachine->Update();

		// update our collision primitive
		m_CollisionPrimitive->Position = m_Centre;	

		if(g_Count < 0.0)
		{			
			fired = false;
			g_Count = 3.00f;
		}

		if(laser != NULL)
		{
			// update the laser variables
			laser->setAngle(m_Angle);
			laser->setPosition(m_Centre);
			laser->update();
		}
		
		g_Count -= Engine::GetInstance()->getDt();

	}
}

void Enemy::render(IRenderer *renderer)
{
	if(isDestroyed())
	{
		bool bExplosionDrawn;
		glColor3f(1.0f,1.0f,1.0f);
		if(!GetExplosionDrawn())
		{
			bExplosionDrawn = renderer->renderExplosion(m_Centre.x, m_Centre.y);
			SetExplosionDrawn(bExplosionDrawn);
		}

		laser->setVisible(false);
	}
	else
	{
		BaseEntity::render(renderer);

		if(g_Count < 2.0f)
			laser->setVisible(false);

		if(laser != NULL && !isDestroyed())
			laser->render(renderer);
	}
}

void Enemy::reset()
{
	InitState();

	if(laser != NULL)
	{
		laser->setVisible(false);
		// update the laser variables
		laser->setAngle(m_Angle);
		laser->setPosition(m_Centre);
		laser->update();
	}

	setVisible(false); // make them invisible and let the round state change them
	setDestroyed(false);
	SetAcceleration(Vector2f(0.0f,0.0f));
	setVelocity(Vector2f(0.0f,0.0f));
	setCurrentState(DEAD);
	ClearForce();
}

void Enemy::InitState()
{

		rng.randomise();
		if(rng.random()<=0.5)
		{
			sStateMachine->ChangeState(AttackPlayer::Instance());
		}
		else
	
		sStateMachine->ChangeState(SeekAsteroid::Instance());
}