#include "ExitWindowsScreenState.h"

ExitWindowsScreenState::ExitWindowsScreenState()
: BaseState(ID_EXIT_TO_WINDOWS_STATE.getStr().c_str())
{
	m_pController = NULL;
	m_pSoundsystem = NULL;
}

ExitWindowsScreenState::~ExitWindowsScreenState(void)
{
}

void ExitWindowsScreenState::start()
{
	m_pController = Engine::GetInstance()->getControllerInput();
	// show the exit windows ui page
	Engine::GetInstance()->getGuiSystem()->SelectPage(ID_EXIT_TO_WINDOWS_PAGE.getStr());
}
void ExitWindowsScreenState::stop()
{
	m_pController = NULL;
}
void ExitWindowsScreenState::update()
{
	// only process input on exit screens
	processInput();
}
void ExitWindowsScreenState::processInput()
{
	if(m_pController)
	{
		if(m_pController->ActionKeysActive(ACTIONS_YES, false))
		{
			// Exit the application
			Engine::GetInstance()->doExit(true);
		}
		if(m_pController->ActionKeysActive(ACTIONS_N0 , false))
		{
			StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
	}
}
