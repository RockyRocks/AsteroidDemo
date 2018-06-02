#include "GUI_Component.h"

//For creating a vector to vector<Point>
#include "Character.h"
//OpenGL
#include <glut.h>

namespace GUI
{
	GUI_Component::GUI_Component(const string& name)
	{
		m_name = name;
	}

	GUI_Component::~GUI_Component(void)
	{
	}

	void GUI_Component::SetName(const std::string& name)
	{
		m_name = name;
	}

	std::string GUI_Component::GetName() const
	{
		return m_name;
	}

	void GUI_Component::SetLabel(const std::string& lable)
	{
		UpdateCharacters(lable);
	}

	void GUI_Component::SetMiddlePosition()
	{
		// removed the hard-coded screen width
		// Chi
		static int screenWidth = GraphicsManager::GetInstance()->getWidth();
		int isize = m_property.characters.size();
		m_property.x = screenWidth/2-15*m_property.size*(int)isize/2;
	}

	//void GUI_Component::SetType(COMPONENT_TYPE type)
	//{
	//	m_type = type;
	//}

	//GUI_Component::COMPONENT_TYPE GUI_Component::GetType() const
	//{
	//	return m_type;
	//}

	void GUI_Component::SetSelected(bool b)
	{
		m_bSelected = b;
	}

	bool GUI_Component::GetSelected() const
	{
		return m_bSelected;
	}

	void GUI_Component::SetDisplayProperty(const DisplayProperty& myproperty)
	{
		m_property = myproperty;
	}

	GUI_Component::DisplayProperty& GUI_Component::GetDisplayProperty()
	{
		return m_property;
	}


	void GUI_Component::Render()
	{
		//iterator pointing to start of a vector of type <Character*>
		vector<Character*>::iterator charIter = m_property.characters.begin();

			//Scale the letters
		float size = m_property.size;
		

		glColor3fv(m_property.color.ptr());	

			//translate the letter to the position where we want to draw it
		glPushMatrix();
		glTranslatef(m_property.x, m_property.y, 0.f);
		glScalef(size, size, 1.f);

		//Iterate through the elements in characters
		for(charIter; charIter != m_property.characters.end(); charIter++) 
		{

			//Pointer to the first element of the characters vector of type Point
			vector<Character::Point> thePoints;
			thePoints = (*charIter)->GetPointsVec();

			//iterator pointing to the first element of characters vector
			vector<Character::Point>::iterator pointIter = thePoints.begin();

			glBegin(GL_LINE_STRIP);
			//Iterate through all the points in the vector and draw them
			for(pointIter; pointIter != thePoints.end(); pointIter++) 
			{
				glVertex2f( pointIter->m_x, pointIter->m_y);
				//glVertex2f( 0.f, 0.f);
				//glVertex2f( 100.f, 0.f);
			}
			glEnd();
			//do a translation so that the next character is alongside and not on top
			//of the previous character drawn
			glTranslatef(15.f, 0.f, 0.f);
		}
		glPopMatrix();

		//glFlush();
		//glutSwapBuffers();
	}

	void GUI_Component::UpdateCharacters(const string& name)
	{
		m_property.characters.clear();
		
		Character* ptemp = 0;

		int legth = name.size();
		for (int i=0;i<legth;i++)
		{
			ptemp = GetCharacterManager().GetCharacterPointer(name[i]);
			assert(ptemp != 0);
			m_property.characters.push_back(ptemp);
		}
	}
}

