#pragma once

#include "GUI_Component.h"
#include "PreRequisite.h"

namespace GUI
{
	class GUI_Page
	{
	public:
		typedef std::vector<GUI_Component> ComponentVec;
		typedef ComponentVec::iterator ComponentVecIter;
	public:
		GUI_Page(const string& name);
		~GUI_Page(void);

		GUI_Component* AddComponent(const string& name);
		GUI_Component* GetComponent(const string& name);


		void SetName(const std::string& name);
		std::string GetName() const;
		void SetSelected(bool b);
		bool GetSelected() const;

		void RenderComponents();

		ComponentVec& GetComponentVec() ;


	private:
		ComponentVec m_componentVec;
		ComponentVecIter m_iter;

		std::string m_name;
		bool m_bSelected;

		//not used for the PC version
		//GUI_Component* m_activeComponent;
	};
}

