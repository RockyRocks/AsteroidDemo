#include "GUISystem.h"

namespace GUI
{
	GUISystem::GUISystem()
	{

		m_activePage = 0;
	}

	GUISystem::~GUISystem(void)
	{
		m_activePage = 0;
	}


	bool GUISystem::InitializeGUI()
	{
		GetCharacterManager().InitializeCharacters();
		return true;
	}

	bool GUISystem::DestroyGUI()
	{
		m_activePage = NULL;

		return true;

	}

	GUI_Page* GUISystem::AddPage(const string& name)
	{
		GUI_Page tempPage(name);
		m_pageVec.push_back(tempPage);
		m_activePage = &m_pageVec.back();
		return m_activePage;
	}

	void GUISystem::RemovePage(const string& name)
	{
		PageVecIter iter = m_pageVec.begin();

		for (;iter!=m_pageVec.end();iter++)
		{
			if (iter->GetName() == name)
			{
				m_pageVec.erase(iter);
				m_activePage = 0;
				break;
			}
		}
	}

	GUI_Page* GUISystem::GetPage(const string& name)
	{
		PageVecIter m_iter = m_pageVec.begin();
		for (;m_iter!=m_pageVec.end();m_iter++)
		{
			if (m_iter->GetName() == name)
			{
				return &(*m_iter);
			}
		}
		return 0;

	}
	GUI_Page* GUISystem::GetActivePage()
	{
		return m_activePage;
	}


	bool GUISystem::SelectPage(const std::string& pagename)
	{
		PageVecIter iter = m_pageVec.begin();

		for (;iter!=m_pageVec.end();iter++)
		{
			if (iter->GetName()== pagename)
			{
				m_activePage = &(*iter);
				return true;
			}
		}
		return false;
	}


	void GUISystem::RenderPage()
	{
		if (m_activePage != 0)
		{
			m_activePage->RenderComponents();
		}
	}
}
