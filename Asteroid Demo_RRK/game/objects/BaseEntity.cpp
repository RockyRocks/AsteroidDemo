#include "BaseEntity.h"
#include <glut.h>

BaseEntity::BaseEntity(const std::string &name, const Vector2f &centre)
: m_Colour(1.0f,1.0f,1.0f,1.0f), m_Centre(centre), 
	m_bIsVisible(false), m_EntityIdent(HashedString(name.c_str())),
	m_Matrix(Matrix44f::IDENTITY), m_Speed(0.0f), 
	m_Velocity(0.0f,0.0f), m_Angle(0.0f),bExplosionDrawn(false)
	
{
	m_CollisionPrimitive = NULL;
	mass=1;
	owner = NULL;
	owning = NULL;
	m_State = ALIVE;

	m_IsDestroyed = false;
	m_AngleAcceleration = 1.0f;
	m_Drag = 0.96f;
	m_MaxSpeed = 0.2f;
	m_Force = Vector2f(0,0);

	m_Matrix[0][2] = m_Centre.x;
	m_Matrix[1][2] = m_Centre.y;
}

BaseEntity::~BaseEntity(void)
{
	m_VectorList.clear();

	if(m_CollisionPrimitive != NULL)
		delete m_CollisionPrimitive;
}

void BaseEntity::forward()
{
	float radians = MathLib::degToRad(m_Angle);
	m_Heading.x = -sin(radians);
	m_Heading.y = cos(radians);

	AddForce(m_Heading*300);
}

void BaseEntity::fire()
{
}

void BaseEntity::turnLeft()
{
	rotate(3.0f);
}
void BaseEntity::turnRight()
{
	rotate(-3.0f);
}

void BaseEntity::rotate(float deg)
{
	// find the angular velocity using the angle we need to turn (in degrees)
	m_Angle += deg * m_AngleAcceleration * Engine::GetInstance()->getDt(); //WinTimer::GetInstance()->getDeltaTime();
}

bool BaseEntity::loadVertexList(const char *filename)
{
	if(!EntityManager::GetInstance()->loadVertexFile(filename, &m_VectorList))
	{
		std::string s= "Cannot load file: ";
		s.append(filename);
		s.append(" for entity: ");
		s.append(m_EntityIdent.getStr());
		Logger::GetInstance()->printMsg(ERRORLOG, s.c_str());

		return false;
	}
	else
		return true;
}


void BaseEntity::render(IRenderer *renderer)
{
	if(m_bIsVisible) // only draw if it's visible
	{
		glPushMatrix();
		// change the colour of the entity
		float r = m_Colour.r;
		float g = m_Colour.g;
		float b = m_Colour.b;

		glColor3f(r, g, b);
		glTranslatef(getPosition().x, getPosition().y, 0.0f);
		glRotatef(getAngle(), 0.f, 0.f, 1.f);

		// now draw the vertices
		glBegin(GL_LINE_STRIP);
		const VertexList *pVertList = getVertexListPointer();

		for(int j=0; j <(int) pVertList->size(); j++)
		{
			float x = pVertList->at(j).x;
			float y = pVertList->at(j).y;

			glVertex2f(x, y);
		}
		glEnd();

		glPopMatrix();
	}
}

void BaseEntity::update()
{
	float dt = Engine::GetInstance()->getDt(); //WinTimer::GetInstance()->getDeltaTime();
	if(m_Velocity.length()>m_MaxSpeed)
	{
		m_Velocity.normalise();
		Vector2f dir=m_Velocity;
		m_Velocity=dir*m_MaxSpeed;
	}
	
	m_Acceleration=m_Force*GetInverseMass();

	m_Velocity+=m_Acceleration*dt;

	m_Velocity*=m_Drag;

	m_Centre+=m_Velocity*dt;
	
	ClearForce();

	// Update the children
	ChildrenList::iterator it = m_Children.begin();
	while(it != m_Children.end())
	{
		(*it)->update();
		++it;
	}
}
