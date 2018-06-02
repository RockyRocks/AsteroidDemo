#include "Laser.h"

Laser::Laser(const Vector2f &startPt, const Vector2f &endPt)
: BaseEntity(ID_LASER.getStr().c_str(), Vector2f(0.0,0.0)) // start the translation from point 0,0. when we draw the line, it will be from the start pt & end pt specified
// with respect to the 0,0 point.
{
	m_RotMtx.identity();

	m_CurrStartPt = startPt;
	m_CurrEndPt = endPt;

	m_Colour.r = 0.0f;
	m_Colour.g = 0.0f;
	m_Colour.b = 1.0f;
	m_Colour.a = 1.0f;

	m_CollisionPrimitive = new CollisionLine(m_CurrStartPt, m_CurrEndPt);

	//setVisible(true);

	// register this entity with the entity manager
	EntityManager::GetInstance()->registerEntity(this);
}


void Laser::setPosition(const Vector2f &newPos)
{
	m_CurrStartPt = newPos;
}

void Laser::setAngle(const float angle)
{
	m_Angle = angle;

	float radians = MathLib::degToRad(m_Angle);

	Vector2f head;
	head.x = -sin(radians);
	head.y = cos(radians);
	head.normalise();

	m_CurrStartPt = m_CurrStartPt;
	m_CurrEndPt = m_CurrStartPt + (head * 135);
}

void Laser::update()
{	
	CollisionLine *cl = (CollisionLine*) m_CollisionPrimitive;
	cl->StartPoint = m_CurrStartPt;
	cl->EndPoint = m_CurrEndPt;
}

void Laser::render(IRenderer *renderer)
{
	if(m_bIsVisible) // only draw if it's visible
	{
		glPushMatrix();
		// change the colour of the entity
		float r = m_Colour.r;
		float g = m_Colour.g;
		float b = m_Colour.b;

		glColor3f(r, g, b);

		// now draw the vertices
		glBegin(GL_LINES);
		const VertexList *pVertList = getVertexListPointer();

		for(int j=0; j < 2; j++)
		{			
			glVertex2f(m_CurrStartPt.x, m_CurrStartPt.y);
			glVertex2f(m_CurrEndPt.x, m_CurrEndPt.y);
		}
		glEnd();
		glPopMatrix();
	}
}

Laser::~Laser(void)
{
}
