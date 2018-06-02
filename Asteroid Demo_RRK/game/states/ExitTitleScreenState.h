#ifndef __EXIT2TITLE_H
#define __EXIT2TITLE_H

#include "..\GameConstants.h"
#include "..\..\common\statemanager\basestate.h"

class ExitTitleScreenState : public BaseState
{
public:
	ExitTitleScreenState();
	virtual ~ExitTitleScreenState(void);

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void processInput();
	virtual void load() {}
	virtual void unload() {}
};

#endif