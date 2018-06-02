#ifndef __SETUPSTATE_H
#define __SETUPSTATE_H

#include "..\..\common\statemanager\basestate.h"
#include "..\..\engine\gfx\GraphicsManager.h"
#include "..\..\common\StateManager\StateManager.h"
#include "..\..\engine\engine.h"
#include "..\GameConstants.h"

#include "MainGameState.h"
#include "TitleScreenState.h"
#include "ExitTitleScreenState.h"
#include "ExitWindowsScreenState.h"
#include "OptionState.h"
#include "ScoreState.h"

// SetupState Description
//
// Sets up everything about the game, states, eventlisteners, scenes & ui pages
// This state should only be run AT THE BEGINNING OF THE GAME.
class SetupState :	public BaseState
{
public:
	SetupState();
	virtual ~SetupState();

	virtual void start();

	// Don't need the following functions
	virtual void stop() {}
	virtual void update() {}
	virtual void load() {}
	virtual void unload() {}
	virtual void processInput() {}
};

#endif
