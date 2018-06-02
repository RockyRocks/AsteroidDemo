#ifndef __EXIT2WINDOWS_H
#define __EXIT2WINDOWS_H

#include "..\GameConstants.h"
#include "..\..\common\statemanager\basestate.h"

class ExitWindowsScreenState :	public BaseState
{
public:
	ExitWindowsScreenState();
	virtual ~ExitWindowsScreenState(void);

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void processInput();
	virtual void load() {}
	virtual void unload() {}
};

#endif