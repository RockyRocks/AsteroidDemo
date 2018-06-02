#include "OptionState.h"

OptionState::OptionState(void)
: BaseState(ID_OPTION_STATE.getStr().c_str())
{
	m_pController = NULL;
	m_pSoundsystem = NULL;
}

OptionState::~OptionState(void)
{
}

void OptionState::start()
{
	m_pController = Engine::GetInstance()->getControllerInput();
	// show the exit title ui page
	Engine::GetInstance()->getGuiSystem()->SelectPage(ID_OPTION_PAGE.getStr());
}
void OptionState::stop()
{
	m_pController = NULL;
}
void OptionState::update()
{
	processInput();
}

void OptionState::processInput()
{
	static bool f1=true;
	static bool f4=true;
	static bool f5=true;
	static bool f2=false;
	static bool f3=false;
	if(m_pController != NULL)
	{
		m_pController->Update();
		if(m_pController->ActionKeysActive(ACTIONS_F1 ,false))
		{
			f1 = !f1;
			if (f1)
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f1")->SetLabel("F1 _ TOGGLE BACKDROP (ON)");

			} 
			else
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f1")->SetLabel("F1 _ TOGGLE BACKDROP (OFF)");
			}
			
		}
		if(m_pController->ActionKeysActive(ACTIONS_F2 ,false))
		{
			f2 = !f2;
			if (f2)
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f2")->SetLabel("F2 _ TOGGLE ANTIALIAS (OFF)");
			} 
			else
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f2")->SetLabel("F2 _ TOGGLE ANTIALIAS (ON)");
			}
		}
		if(m_pController->ActionKeysActive(ACTIONS_F3 ,false))
		{
			f3 = !f3;
			if (f3)
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f3")->SetLabel("F3 _ TOGGLE FLICKER (OFF)");
			} 
			else
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f3")->SetLabel("F3 _ TOGGLE FLICKER (ON)");
			}
		}
		if(m_pController->ActionKeysActive(ACTIONS_F4 ,false))
		{
			f4 = !f4;
			if (f4)
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f4")->SetLabel("F4 _ TOGGLE COLOR (ON)");
			} 
			else
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f4")->SetLabel("F4 _ TOGGLE COLOR (OFF)");
			}
		}
		if(m_pController->ActionKeysActive(ACTIONS_F5 ,false))
		{
			f5 = !f5;
			if (f5)
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f5")->SetLabel("F5 _ TOGGLE SOUND (ON)");
			} 
			else
			{
				GUI::GUISystem::GetInstance()->GetPage(ID_OPTION_PAGE.getStr())->GetComponent("f5")->SetLabel("F5 _ TOGGLE SOUND (OFF)");
			}
		}
		if(m_pController->ActionKeysActive(ACTIONS_F6 ,false))
		{
			
		}
		if(m_pController->ActionKeysActive(ACTIONS_F7,false))
		{
			
		}
		if(m_pController->ActionKeysActive(ACTIONS_F8,false))
		{
			
		}
		if(m_pController->ActionKeysActive(ACTIONS_F9,false))
		{
			
		}
		if(m_pController->ActionKeysActive(ACTIONS_QUIT,false))
		{
			// go back to title screen
			StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
	}
}