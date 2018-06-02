#include "GUI_Page.h"

namespace GUI
{
	GUI_Page::GUI_Page(const string& name)
	{
		m_bSelected = false;
		//m_activeComponent = 0;

		m_name = name;
	}

	GUI_Page::~GUI_Page(void)
	{
		m_bSelected = false;
		//m_activeComponent = 0;
	}

	void GUI_Page::SetName(const std::string& name)
	{
		m_name = name;
	}

	std::string GUI_Page::GetName() const
	{
		return m_name;
	}

	GUI_Component* GUI_Page::AddComponent(const string& name)
	{
		GUI_Component temp(name);
		m_componentVec.push_back(temp);
		return &m_componentVec.back();
	}

	GUI_Component* GUI_Page::GetComponent(const string& name)
	{
		m_iter = m_componentVec.begin();
		for (;m_iter!=m_componentVec.end();m_iter++)
		{
			if (m_iter->GetName() == name)
			{
				return &(*m_iter);
			}
		}
		return 0;
	}



	void GUI_Page::SetSelected(bool b)
	{
		m_bSelected = b;
	}

	bool GUI_Page::GetSelected() const
	{
		return m_bSelected;
	}

	void GUI_Page::RenderComponents()
	{
		ComponentVecIter iter = m_componentVec.begin();
		for (;iter!=m_componentVec.end();iter++)
		{
			iter->Render();
		}
	}

	GUI_Page::ComponentVec& GUI_Page::GetComponentVec()
	{
		return m_componentVec;
	}
}

