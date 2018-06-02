#include "SetupState.h"

SetupState::SetupState()
: BaseState(ID_SETUP_STATE.getStr().c_str())
{
	m_pController = NULL;
	m_pSoundsystem = NULL;
}

SetupState::~SetupState(void)
{
}

void SetupState::start()
{


	//ADD GUISystem Jason
	// Create the title screen UI Pages
	using namespace GUI;
	//////////////////////////////////////////////////////////////////////
	//*******************************************************************
	//////////////////////////////////////////////////////////////////////
	// title screen UI page creation
	GUISystem::GetInstance()->InitializeGUI();
	GUI_Page* page = GUISystem::GetInstance()->AddPage(ID_TITLE_PAGE.getStr());
	GUI_Component* component = 0;
	GUI_Component::DisplayProperty display;
	//component1
	component = page->AddComponent(ID_START_CMPNT.getStr());
	//display.x = 10;
	display.y = 200;
	display.size = 1.5;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PRESS ENTER TO START");
	component->SetMiddlePosition();
	
	//component2
	component = page->AddComponent(ID_SELECT_PLAYER_CMPNT.getStr());
	//display.x = 10;
	display.y = 170;
	display.size = 1;
	display.color = Color::PINK;
	component->SetDisplayProperty(display);
	component->SetLabel("USE ARROWS <> TO SELECT PLAYERS (1)");
	component->SetMiddlePosition();
	//component3
	component = page->AddComponent(ID_SELECT_DIFFICULTY_CMPNT.getStr());
	display.x = 10;
	display.y = 150;
	display.size = 1;
	display.color = Color::PINK;
	component->SetDisplayProperty(display);
	component->SetLabel("USE ARROWS -= TO SET DIFFICULTY (NORMAL)");
	component->SetMiddlePosition();
	//component4
	component = page->AddComponent(ID_OPTIONS_CMPNT.getStr());
	display.x = 10;
	display.y = 100;
	display.size = 1.5;
	display.color = Color::GREEN;
	component->SetDisplayProperty(display);
	component->SetLabel("PRESS TAB FOR OPTIONS");
	component->SetMiddlePosition();
	//component5
	component = page->AddComponent(ID_VIEWSCORES_CMPNT.getStr());
	display.x = 10;
	display.y = 70;
	display.size = 1.5;
	display.color = Color::GREEN;
	component->SetDisplayProperty(display);
	component->SetLabel("PRESS SPACE TO VIEW SCORES");
	component->SetMiddlePosition();
	//component6
	component = page->AddComponent("by Rakesh");
	display.x = 10;
	display.y = 40;
	display.size = 1.5;
	display.color = Color::RED;
	component->SetDisplayProperty(display);
	component->SetLabel("By Rakesh");
	component->SetMiddlePosition();
	//component7
	component = page->AddComponent("Asteroid");
	display.x = 10;
	display.y = 500;
	display.size = 5;
	display.color = Color::YELLOW;
	component->SetDisplayProperty(display);
	component->SetLabel("Asteroid");
	component->SetMiddlePosition();
	// component8
	component = page->AddComponent(ID_GAMEOVER_CMPNT.getStr());
	display.x = 10;
	display.y = 450;
	display.size = 1;
	display.color = Color::RED;
	component->SetDisplayProperty(display);
	component->SetLabel("");
	component->SetMiddlePosition();
	//////////////////////////////////////////////////////////////////////
	//*******************************************************************
	//////////////////////////////////////////////////////////////////////
	//option page
	page = GUISystem::GetInstance()->AddPage(ID_OPTION_PAGE.getStr());
	int diff = 30;
	//Rip off
	component = page->AddComponent("Asteroid1");
	display.x = 10;
	display.y = 500;
	display.size = 5;
	display.color = Color::YELLOW;
	component->SetDisplayProperty(display);
	component->SetLabel("Asteroid");
	component->SetMiddlePosition();
	//component1
	component = page->AddComponent("f1");
	display.x = 200;
	display.y = 400;
	display.size = 1;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F1 _ TOGGLE BACKDROP (ON)");

	//component2
	component = page->AddComponent("f2");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F2 _ TOGGLE ANTIALIAS (OFF)");

	//component3
	component = page->AddComponent("f3");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F3 _ TOGGLE FLICKER (OFF)");

	//component4
	component = page->AddComponent("f4");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F4 _ TOGGLE COLOR (ON)");

	//component5
	component = page->AddComponent("f5");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F5 _ TOGGLE SOUND (ON)");

	//component6
	component = page->AddComponent("f6");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F6 _ P1 CONTROL (KEYBOARD)");

	//component7
	component = page->AddComponent("f7");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F7 _ P2 CONTROL (KEYBOARD)");

	//component8
	component = page->AddComponent("f8");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F8 _ P1 REDEFINE KEYS");

	//component9
	component = page->AddComponent("f9");
	display.y -=diff;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F9 _ P2 REDEFINE KEYS");

	//component10
	component = page->AddComponent("f1f4");
	display.y -=diff*2;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("F1 _ F4 ALSO AVAILABLE DURING GAME");
	component->SetMiddlePosition();
	//component11
	component = page->AddComponent("component11");
	display.y -=diff;
	display.color = Color::GREEN;
	component->SetDisplayProperty(display);
	component->SetLabel("START GAME WITH /WINDOW ON THE");
	component->SetMiddlePosition();
	//component12
	component = page->AddComponent("component12");
	display.y -=diff;
	display.color = Color::GREEN;
	component->SetDisplayProperty(display);
	component->SetLabel("COMMANDLINE TO RUN GAME IN WINDOW");
	component->SetMiddlePosition();
	//////////////////////////////////////////////////////////////////////
	//*******************************************************************
	//////////////////////////////////////////////////////////////////////
	//score page
	page = GUISystem::GetInstance()->AddPage(ID_SCORE_PAGE.getStr());
	//Rip off
	component = page->AddComponent("asteroid2");
	display.x = 10;
	display.y = 500;
	display.size = 5;
	display.color = Color::YELLOW;
	component->SetDisplayProperty(display);
	component->SetLabel("Asteroid");
	component->SetMiddlePosition();
	//component1
	component = page->AddComponent("score1");
	display.x = 200;
	display.y = 400;
	display.size = 1;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("LATEST SCORES");
	component->SetMiddlePosition();

	//component2
	component = page->AddComponent("score2");
	display.y -=diff;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PLAYER 1 > 00000");
	component->SetMiddlePosition();

	//component3
	component = page->AddComponent("score3");
	display.y -=diff;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PLAYER 2 > 00000");
	component->SetMiddlePosition();

	//component4
	component = page->AddComponent("score4");
	display.y -=diff;
	display.color = Color::RED;
	component->SetDisplayProperty(display);
	component->SetLabel("ROUND REACHED 00");
	component->SetMiddlePosition();

	//component5
	component = page->AddComponent("score5");
	display.y -=diff*2;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("HIGHSCORE _ NORMAL MODE");
	component->SetMiddlePosition();
	//component6
	component = page->AddComponent("score6");
	display.y -=diff;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PLAYER 1 > 00000 > (ROUND 0)");
	component->SetMiddlePosition();
	//component7
	component = page->AddComponent("score7");
	display.y -=diff;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PLAYER 2 > 00000 > (ROUND 0)");
	component->SetMiddlePosition();
	//component8
	component = page->AddComponent("score8");
	display.y -=diff*2;
	display.color = Color::BLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("HIGHSCORE _ EASY MODE");
	component->SetMiddlePosition();
	//component9
	component = page->AddComponent("score9");
	display.y -=diff;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PLAYER 1 > 00000 > (ROUND 0)");
	component->SetMiddlePosition();
	//component10
	component = page->AddComponent("score10");
	display.y -=diff;
	display.color = Color::LIGHTBLUE;
	component->SetDisplayProperty(display);
	component->SetLabel("PLAYER 2 > 00000 > (ROUND 0)");
	component->SetMiddlePosition();
	//component11
	component = page->AddComponent("score11");
	display.y -=diff*2;
	display.color = Color::GREEN;
	component->SetDisplayProperty(display);
	component->SetLabel("PRESS SPACE _ ESC TO RETURN");
	component->SetMiddlePosition();
	////////////////////////////////////////////////////////////////////////
	////*******************************************************************
	////////////////////////////////////////////////////////////////////////
	//// main game ui page creation (Score, Round)
	page = GUISystem::GetInstance()->AddPage(ID_MAIN_PAGE.getStr());
	component = page->AddComponent(ID_ROUND_CMPNT.getStr());
	display.x = GraphicsManager::GetInstance()->getWidth() / 2;
	display.y = GraphicsManager::GetInstance()->getHeight() - 10;
	display.size = 0.7;
	display.color = Color::WHITE;
	component->SetDisplayProperty(display);
	component->SetLabel("ROUND 1");
	component->SetMiddlePosition();

	component = page->AddComponent(ID_SCORE_CMPNT.getStr());
	display.x = GraphicsManager::GetInstance()->getWidth() - 70;
	display.y = GraphicsManager::GetInstance()->getHeight()- 10;
	display.size = 0.7;
	display.color = Color::WHITE;
	component->SetDisplayProperty(display);
	component->SetLabel("00000");

	component = page->AddComponent(ID_SCORE2_CMPNT.getStr());
	display.x = 70;
	display.y = GraphicsManager::GetInstance()->getHeight()- 10;
	display.size = 0.7;
	display.color = Color::WHITE;
	component->SetDisplayProperty(display);
	component->SetLabel(""); // keep the label invisible for now, this will be filled in by the MainGameState
							// whenever player2 is available
	//component->SetMiddlePosition();
	
	//////////////////////////////////////////////////////////////////////
	//*******************************************************************
	//////////////////////////////////////////////////////////////////////
	//exit to title screen page creation
	page = GUISystem::GetInstance()->AddPage(ID_EXIT_TO_TITLE_PAGE.getStr());
	component = page->AddComponent(ID_EXIT_CMPNT.getStr());
	display.x = GraphicsManager::GetInstance()->getWidth() / 2;
	display.y = GraphicsManager::GetInstance()->getHeight() - 50;
	display.size = 1.5;
	display.color = Color::RED;
	component->SetDisplayProperty(display);
	component->SetLabel("EXIT TO MENU? (Y/N)");
	component->SetMiddlePosition();

	// exit to windows
	page = GUISystem::GetInstance()->AddPage(ID_EXIT_TO_WINDOWS_PAGE.getStr());
	component = page->AddComponent(ID_EXIT_CMPNT.getStr());
	display.x = GraphicsManager::GetInstance()->getWidth() / 2;
	display.y = GraphicsManager::GetInstance()->getHeight() - 50;
	display.size = 1.5;
	display.color = Color::RED;
	component->SetDisplayProperty(display);
	component->SetLabel("EXIT TO WINDOWS? (Y/N)");
	component->SetMiddlePosition();

	// Setup the states
	IState * pState = new MainGameState(ID_MAIN_STATE.getStr().c_str());
	StateManager::GetInstance()->addState(pState);

	pState = new TitleScreenState(ID_TITLE_STATE.getStr().c_str());
	StateManager::GetInstance()->addState(pState);

	pState = new ExitTitleScreenState();
	StateManager::GetInstance()->addState(pState);

	pState = new ExitWindowsScreenState();
	StateManager::GetInstance()->addState(pState);

	pState = new OptionState();
	StateManager::GetInstance()->addState(pState);

	pState = new ScoreState();
	StateManager::GetInstance()->addState(pState);

	// set the current state to be the title screen
	StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());

	// reload the state in the engine
	Engine::GetInstance()->loadState();

	page = NULL;
	component = NULL;
	pState = NULL;
}