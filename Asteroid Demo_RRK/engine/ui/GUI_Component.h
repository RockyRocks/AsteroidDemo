#pragma once
#include "PreRequisite.h"

#include "Color.h"
#include "CharcterManager.h"
#include "..\gfx\GraphicsManager.h"



namespace GUI
{
	class Character;

	class GUI_Component
	{
	public:
		//typedef enum Type
		//{
		//	BUTTON,
		//	TEXT
		//}COMPONENT_TYPE;

		typedef struct DisplayProperty
		{
			int x,y;//position
			float size;//size
			Color color;//color
			vector<Character*> characters;//characters

		}DisplayProperty;

	public:
		GUI_Component(const string& name);
		~GUI_Component(void);

		void SetName(const std::string& name);
		std::string GetName() const;

		void SetLabel(const std::string& lable);
		void SetMiddlePosition();

		//void SetType(COMPONENT_TYPE type);
		//COMPONENT_TYPE GetType() const;

		void SetSelected(bool b);
		bool GetSelected() const;

		void SetDisplayProperty(const DisplayProperty& myproperty);
		DisplayProperty& GetDisplayProperty();

		void Render();

	private:
		void UpdateCharacters(const string& name);

	private:
		std::string m_name;

		//COMPONENT_TYPE m_type;

		bool m_bSelected;

		DisplayProperty m_property;


	};

}