#include "Player.h"

Player::Player(const std::string &name, const Vector2f &centre)
: BaseEntity(name, centre)
{
	m_Heading=Vector2f(0,1);
	mass=1;
	m_MaxSpeed = 300.0f;
	m_Drag = 0.98f;
	m_AngleAcceleration = 80.0f;

	m_Matrix = m_Matrix.IDENTITY;
	m_Matrix[0][2] = m_Centre.x;
	m_Matrix[1][2] = m_Centre.y;

	m_Colour.r = 1.0f;
	m_Colour.g = 1.0f;
	m_Colour.b = 1.0f;
	m_Colour.a = 1.0f;

	m_CollisionPrimitive = new CollisionCircle(16.0f);
	m_CollisionPrimitive->Position = m_Centre;
	setVisible(true);

	// register this entity with the entity manager
	EntityManager::GetInstance()->registerEntity(this);
}

void Player::reset()
{
	setCurrentState(SPAWNING);
}

Player::~Player(void)
{
}

void Player::fire()
{
	IEntity *pBullet = NULL;
	
	if(m_Children.size() > 0)
	{
		for(int i=0; i <(int) m_Children.size(); ++i)
		{
			pBullet = m_Children.at(i);
			if(pBullet->isVisible() == false) // find the first bullet available
			{
				// set the bullet's initial positions
				pBullet->setPosition(m_Centre);
				pBullet->SetAcceleration(Vector2f(0.0f, 0.0f));
				pBullet->setVelocity(Vector2f(0.0f, 0.0f));
				pBullet->setAngle(m_Angle);
				pBullet->setVisible(true);

				// play the fire sound
				Engine::GetInstance()->getSoundSystem()->play(7);
				break;
			}
		}	
	}
}

void Player::render(IRenderer *renderer)
{
	BaseEntity::render(renderer);
}


void Player::update()
{
	BaseEntity::update();

	// update our collision primitive
	m_CollisionPrimitive->Position = m_Centre;
}