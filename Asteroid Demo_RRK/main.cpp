//#include "..\Utils\MathLib.h"
//#include "vld.h"

#include <vector>
#include <iostream>
#include <sstream>

#include "common\StateManager\StateManager.h"
#include "game\states\SetupState.h"
#include "game\GameConstants.h"
#include "engine\Engine.h"

void Update();
void Render();
void Idle();

int main(int argc,char** argv)
{	
	//// Check for memory leaks
	//#ifdef	_DEBUG
	//	// Get Current flag
	//	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ; 
	//	// Turn on leak-checking bit
	//	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ; 
	//	// Set flag to the new value
	//	_CrtSetDbgFlag(flag) ; 
	//#endif	_DEBUG

	//_CrtSetBreakAlloc(506);

	// create the main game state
	IState *mainGameState = new SetupState;
	// add to the StateManager
	StateManager::GetInstance()->addState(mainGameState);
	StateManager::GetInstance()->makeCurrentState(ID_SETUP_STATE.getHashValue());

	glutInit(&argc,argv);
	Engine::GetInstance()->start();
	//coreEngine.start();
	glutDisplayFunc(Render);
	glutIdleFunc(Idle);
	
	// This is a *very* *very* hacky way of exiting gracefully. Whenever the escape button is pressed
	// the engine will throw an error which will exit out of the glutMainLoop and the catch routine
	// will catch this and tell the engine to stop & destroy itself.
	try
	{
		glutMainLoop();
	}
	catch(const char *e)
	{
		Engine::GetInstance()->stop();
		Engine::GetInstance()->DestroyInstance();
	}

	return 0;
};

void Update()
{
	// engine update?
};
void Render()
{
	Engine::GetInstance()->render();
	//coreEngine.render();
};

void Idle()
{
	
	Engine::GetInstance()->render();
	//coreEngine.update();
};