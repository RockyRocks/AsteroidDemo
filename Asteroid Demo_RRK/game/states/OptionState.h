#ifndef __OPTIONSTATE_H
#define __OPTIONSTATE_H

#include "..\..\common\statemanager\basestate.h"
#include "..\GameConstants.h"

class OptionState :
	public BaseState
{
public:
	OptionState();
	virtual ~OptionState(void);

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void processInput();
	virtual void load() {}
	virtual void unload() {}
};

#endif
