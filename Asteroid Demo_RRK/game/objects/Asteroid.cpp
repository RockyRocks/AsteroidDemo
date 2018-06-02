#include "Asteroid.h"

Asteroid::Asteroid(const std::string &name, const Vector2f &centre)
: BaseEntity(name, centre)
{
	m_MaxSpeed = 7.0f;
	m_Drag = 2.0f; // no drag for Asteroids
	
	m_Colour.r = 0.0f;
	m_Colour.g = 1.0f;
	m_Colour.b = 0.0f;
	m_Colour.a = 1.0f;

// 	m_VectorList.push_back(Vector2f(0.0f, 10.0f));
// 	m_VectorList.push_back(Vector2f(10.0f, -10.0f));
// 	m_VectorList.push_back(Vector2f(-10.0f, -10.0f));
// 	m_VectorList.push_back(Vector2f(0.0f, 10.0f));
	m_VectorList.push_back(Vector2f(10.0f,20.5f));
	m_VectorList.push_back(Vector2f(5.5f, 10.5f));
	m_VectorList.push_back(Vector2f(10.0f, 0.0f));
	m_VectorList.push_back(Vector2f(10.0f, -10.0f));
	m_VectorList.push_back(Vector2f(-10.0f, -10.0f));
	m_VectorList.push_back(Vector2f(-10.0f, 0.0f));
	m_VectorList.push_back(Vector2f(-10.0f, 10.5f));
	m_VectorList.push_back(Vector2f(-5.0f, 5.0f));
	m_VectorList.push_back(Vector2f(-10.0f, 20.5f));
	m_VectorList.push_back(Vector2f(0.0f, 20.5f));
	m_VectorList.push_back(Vector2f(10.0f, 20.5f));
	setVisible(true);

	// register this entity with the entity manager
	EntityManager::GetInstance()->registerEntity(this);

	// create a new collision primitive
	m_CollisionPrimitive = new CollisionCircle(20.0f);
	m_CollisionPrimitive->Position = m_Centre;

}

Asteroid::~Asteroid()
{
	//delete sStateMachine;
}

void Asteroid::update()
{
	BaseEntity::update();
	AddForce(Vector2f(0.0f,-0.001f)*0.001f);
	// update our collision primitive
	m_CollisionPrimitive->Position = m_Centre;
}

void Asteroid::render(IRenderer *renderer)
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
	}
	else
	{
		BaseEntity::render(renderer);
	}
}

void Asteroid::reset()
{
	m_MaxSpeed = 10.0f;
// 	setVisible(true);
// 	setDestroyed(false);
// 	SetAcceleration(Vector2f(0.0f,0.0f));
// 	setVelocity(Vector2f(0.0f,0.0f));
// 	setCurrentState(ALIVE);
// 	ClearForce();

}

// const VertexList* Enemy::getVertexListPointer() const
// {
//	return EntityManager::GetInstance()->getCurrentVertexInstancePointer();
// }