#ifndef __ENGINE_H
#define __ENGINE_H

#include "ai\AIEngine.h"
#include "..\game\objects\EntityManager.h"
#include "..\common\StateManager\StateManager.h"
#include "..\common\StateManager\IState.h"

#include "gfx\TextureManager.h"
#include "gfx\GraphicsManager.h"
#include "input\InputManager.h"
#include "sound\SoundManager.h"
#include "ui\GUISystem.h"

#include "..\game\objects\EntityManager.h"

#include "..\common\utils\Singleton.h"
#include <glut.h>

#ifdef _WIN32
#include "..\common\timer\WinTimer.h"
#endif

// Engine Description
//
// The main entry point to the game engine. Ties the sub-systems together and
// manages the current state it's given.
// Anything in the program can get a const pointer to the systems that the engine handles to 
// perform the task specified by the system pointer.
class Engine : public Singleton<Engine>
{
	friend Singleton<Engine>;

public:
	void start();
	void stop();

	void update();
	void render();
	// Reloads the current state that the engine is using
	void loadState();
	void doExit(bool exit);
	void processEngineInput();

	// methods to get pointers to the internal systems of the engine
	const IState * getCurrentState() const;

	// be careful about modifying these. The engine automatically updates the controller so no need to call this when
	// getting the pointer to it
	IController * getControllerInput();
	ISoundSystem * getSoundSystem();
	GUI::GUISystem * getGuiSystem();

	TextureManager *getTextureManager();

	// you shouldn't really have to get a renderer directly from the engine but it's here
	// just in case (maybe to query the view width/hegitht)
	IRenderer * getRenderer();

	float getDt();

	// deltaTime stored in seconds, used for physics, etc.
	// the target dt is ~16.6ms which is 60fps.
	static float g_DeltaTime;
	static const float g_TimeStep;

private:
	Engine();
	~Engine();
	Engine(const Engine&);
	Engine& operator=(const Engine);

private:	
	bool m_bDoExit;
	ISoundSystem* m_pSoundSystem;
	IRenderer* m_pRenderer;
	IController *m_pController;
	IState* m_pCurrentState;
	TextureManager *m_TextureManager;
	GUI::GUISystem *m_pGUIsystem;
	WinTimer *m_pTimer;
};

inline TextureManager * Engine::getTextureManager()
{
	return m_TextureManager;
}

inline IController * Engine::getControllerInput()
{
	return m_pController;
}

inline ISoundSystem * Engine::getSoundSystem()
{
	return m_pSoundSystem;
}

inline const IState * Engine::getCurrentState() const
{
	return m_pCurrentState;
}

inline GUI::GUISystem * Engine::getGuiSystem()
{
	return m_pGUIsystem;
}

inline IRenderer * Engine::getRenderer()
{
	return m_pRenderer;
}

inline float Engine::getDt()
{
	return m_pTimer->getDeltaTime();
}

inline void Engine::doExit(bool exit)
{
	m_bDoExit = exit;
}

#endif