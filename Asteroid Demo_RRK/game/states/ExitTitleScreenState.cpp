#include "ExitTitleScreenState.h"

ExitTitleScreenState::ExitTitleScreenState()
: BaseState(ID_EXIT_TO_TITLE_STATE.getStr().c_str())
{
	m_pController = NULL;
	m_pSoundsystem = NULL;
}

ExitTitleScreenState::~ExitTitleScreenState(void)
{
}

void ExitTitleScreenState::start()
{
	m_pController = Engine::GetInstance()->getControllerInput(); 
	// show the exit title ui page
	Engine::GetInstance()->getGuiSystem()->SelectPage(ID_EXIT_TO_TITLE_PAGE.getStr());
}
void ExitTitleScreenState::stop()
{
	m_pController = NULL;
}
void ExitTitleScreenState::update()
{
	// only process input on exit screens
	processInput();
}
void ExitTitleScreenState::processInput()
{
	if(m_pController != NULL)
	{
		if(m_pController->ActionKeysActive(ACTIONS_YES, false))
		{
			StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
		if(m_pController->ActionKeysActive(ACTIONS_N0, false))
		{
			StateManager::GetInstance()->makeCurrentState(ID_MAIN_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
	}
}
