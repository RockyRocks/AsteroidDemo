#include "TitleScreenState.h"

static int g_NumberPlayers = 1;
static DIFFICULTY g_Difficulty = NORMAL;

void TitleScreenState::load()
{
}

void TitleScreenState::unload()
{
	// make pointers null so that other
}


TitleScreenState::TitleScreenState(const char * name)
: BaseState(name)
{
	m_pController = NULL;
	m_pSoundsystem = NULL;
	m_bHasAlreadyStarted = false;
	m_Tex = 0;
}

TitleScreenState::~TitleScreenState(void)
{
}

void TitleScreenState::start()
{
	if(!m_bHasAlreadyStarted)
	{
		// Get the pointer to the sound system
		m_pSoundsystem = Engine::GetInstance()->getSoundSystem(); 

		// create a new controller instance
		m_pController = Engine::GetInstance()->getControllerInput();

		m_Tex = Engine::GetInstance()->getTextureManager()->getTexture("backdrop.bmp");
	}

	// select the title screen gui to render
	Engine::GetInstance()->getGuiSystem()->SelectPage(ID_TITLE_PAGE.getStr());

	m_pSoundsystem->stopAllSounds();
	m_pSoundsystem->play(0);

	m_bHasAlreadyStarted = true;
}
void TitleScreenState::stop()
{
	m_pController = NULL;
}
void TitleScreenState::update()
{
	processInput();
}

void TitleScreenState::processInput()
{
	if(m_pController)
	{
		//m_pController->Update();
		// the engine will update the controller for us, all we have to do is poll and see which key was pressed

		if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_TURNLEFT ,true))

		{
			GUI::GUISystem::GetInstance()->GetPage(ID_TITLE_PAGE.getStr())->GetComponent(ID_SELECT_PLAYER_CMPNT.getStr())->SetLabel("USE ARROWS <> TO SELECT PLAYERS (1)");	
			g_NumberPlayers = 1;
		}
		if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_TURNRIGHT ,true))
		{
			GUI::GUISystem::GetInstance()->GetPage(ID_TITLE_PAGE.getStr())->GetComponent(ID_SELECT_PLAYER_CMPNT.getStr())->SetLabel("USE ARROWS <> TO SELECT PLAYERS (2)");			
			g_NumberPlayers = 2;
		}
		if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_MOVEFWD ,true))
		{
			GUI::GUISystem::GetInstance()->GetPage(ID_TITLE_PAGE.getStr())->GetComponent(ID_SELECT_DIFFICULTY_CMPNT.getStr())->SetLabel("USE ARROWS -= TO SET DIFFICULTY (NORMAL)");
			g_Difficulty = NORMAL;
		}
		if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_MOVEDOWN ,true))
		{
			GUI::GUISystem::GetInstance()->GetPage(ID_TITLE_PAGE.getStr())->GetComponent(ID_SELECT_DIFFICULTY_CMPNT.getStr())->SetLabel("USE ARROWS -= TO SET DIFFICULTY (HARD)");
			g_Difficulty = HARD;
		}
		if(m_pController->ActionKeysActive(ACTIONS_ENTER, false))
		{
			GameSettings set;
			set.Difficulty = g_Difficulty;
			set.NumPlayers = g_NumberPlayers;

			// change to the main game state
			StateManager::GetInstance()->makeCurrentState(ID_MAIN_STATE.getHashValue());

			// start a new game, bit of a hack - states shouldn't have knowledge about each other...or should they?
			MainGameState *mgs = (MainGameState*) StateManager::GetInstance()->getCurrentState();
			mgs->setNewGame(true, set);

			Engine::GetInstance()->loadState();
		}
		if(m_pController->ActionKeysActive(ACTIONS_QUIT, false))
		{
			StateManager::GetInstance()->makeCurrentState(ID_EXIT_TO_WINDOWS_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}

		if(m_pController->ActionKeysActive(ACTIONS_TAB , false))
		{
			StateManager::GetInstance()->makeCurrentState(ID_OPTION_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
		if(m_pController->ActionKeysActive(ACTIONS_SPACE, false))
		{
			StateManager::GetInstance()->makeCurrentState(ID_SCORE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
	}
}

void TitleScreenState::render(IRenderer *renderer)
{
	float w = (float) renderer->getViewWidth();
	float h = (float) renderer->getViewHeight();

	renderer->bindTexture(m_Tex);
	// create a quad that fills the screen & put a texture on it
	glBegin(GL_QUADS);
	glVertex2f(w, h); glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, h); glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0, 0.0f); glTexCoord2f(1.0f, 0.0f);
	glVertex2f(w, 0.0f); glTexCoord2f(1.0f, 1.0f);
	glEnd();
	renderer->unbindTexture();
}


