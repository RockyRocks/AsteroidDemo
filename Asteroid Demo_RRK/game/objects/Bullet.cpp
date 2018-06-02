#include "Bullet.h"
#include "..\..\engine\gfx\GraphicsManager.h"

Bullet::Bullet(const std::string &name, const Vector2f &centre)
: BaseEntity(name, Vector2f(0.0f, 2.5f))
{
	m_Drag = 1.0f; // no drag for bullets
	//m_Speed = 0.6f;
	m_MaxSpeed = 300.0f;

	m_VectorList.push_back(Vector2f(0.0f, 0.0f));
	m_VectorList.push_back(Vector2f(0.0f, 5.0f));

	m_Matrix = m_Matrix.IDENTITY;
	m_Matrix[0][2] = m_Centre.x;
	m_Matrix[1][2] = m_Centre.y;

	m_Colour.r = 1.0f;
	m_Colour.g = 1.0f;
	m_Colour.b = 1.0f;
	m_Colour.a = 1.0f;

	m_CollisionPrimitive = new CollisionCircle(1.5f);
	m_CollisionPrimitive->Position = m_Centre;

	// register this entity with the entity manager
	EntityManager::GetInstance()->registerEntity(this);

	// set the bullets to false
	setVisible(false);
}

Bullet::~Bullet(void)
{
}

void Bullet::update()
{
	if(isVisible())
	{
		BaseEntity::update();

		//AddForce(m_Heading*1000);
		forward();

		// update our collision primitive
		m_CollisionPrimitive->Position = m_Centre;

		const float maxHeight = (float) Engine::GetInstance()->getRenderer()->getViewHeight();
		const float maxWidth = (float) Engine::GetInstance()->getRenderer()->getViewWidth();

		// clamp the x,y values for player 1#
		if(m_Centre.x > maxWidth || m_Centre.x < 0.0f 
			|| m_Centre.y > maxHeight || m_Centre.y < 0.0f)
		{
			setVisible(false);
		}

	}
}