#ifndef __TITLESCREENSTATE_H
#define __TITLESCREENSTATE_H

#include "..\..\common\StateManager\BaseState.h"
#include "MainGameState.h"
#include "..\GameConstants.h"
#include "..\AsteroidSettings.h"

class TitleScreenState : public BaseState
{
public:
	TitleScreenState(const char *name);
	virtual ~TitleScreenState(void);

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void processInput();

	virtual void render(IRenderer *renderer);

	virtual void load();
	virtual void unload();

private:
	GLuint m_Tex;
};

#endif