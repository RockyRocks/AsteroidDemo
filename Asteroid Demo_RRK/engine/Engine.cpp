#include "Engine.h"

const float Engine::g_TimeStep  = 1.0f / 60.0f; // 60 fps
float Engine::g_DeltaTime = 1.0f / 60.0f;

bool AnimateNextFrame(int desiredFrameRate)
{
	// TODO: Change the timer for different platforms!!
	static float lastTime = WinTimer::GetInstance()->GetTime() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = WinTimer::GetInstance()->GetTime() * 0.001f; // Get the time (milliseconds = seconds * .001)
	float deltaTime = currentTime - lastTime; // Get the slice of time
	float desiredFPS = 1.0f / desiredFrameRate; // Store 1 / desiredFrameRate

	elapsedTime += deltaTime; // Add to the elapsed time
	lastTime = currentTime; // Update lastTime

	// Check if the time since we last checked is greater than our desiredFPS
	if( elapsedTime > desiredFPS )
	{
		WinTimer::GetInstance()->setDeltaTime(desiredFPS); // Set the delta time
		elapsedTime -= desiredFPS; // Adjust our elapsed time

		// Return true, to animate the next frame of animation
		return true;
	}

	// We don't animate right now.
	return false;
}

Engine::Engine()
{
	m_bDoExit = false;
	m_pRenderer = NULL;
	m_pCurrentState = NULL;
	m_pController = NULL;
}

Engine::~Engine()
{
	//delete m_pController;
	m_pRenderer = NULL;
	m_pCurrentState = NULL;
	m_pController = NULL;
}

void Engine::start()
{
	// Start the timer
	WinTimer::GetInstance()->Initialize();
	m_pTimer = WinTimer::GetInstance();

	// Start the managers
	EntityManager::GetInstance()->start();
	GraphicsManager::GetInstance()->start();
	SoundManager::GetInstance()->start();

	// AI Engine
	AIEngine::GetInstance()->start();

	// Initialize the gfx engine
	m_pRenderer = GraphicsManager::GetInstance()->getRenderer();
	if(m_pRenderer == NULL) 
	{
		Logger::GetInstance()->printMsg(ERRORLOG, " - [Engine] - Failed to initialize Renderer");
	}

	m_pGUIsystem = GUI::GUISystem::GetInstance();

	// Initialize & start the sound engine
	SoundManager::GetInstance()->getSoundSystem()->start();
	m_pSoundSystem = SoundManager::GetInstance()->getSoundSystem();

	//SoundManager::GetInstance()->getSoundSystem()->mute();

	// Start the input engine
	if(!InputManager::GetInstance()->start())
	{
		Logger::GetInstance()->printMsg(ERRORLOG, " - [Engine] - Failed to initialize InputManager");
	}
	// hold an instance of controller for engine specific controller stuff
	m_pController = InputManager::GetInstance()->getController();

	m_TextureManager = TextureManager::GetInstance();
	
	// Start the renderer
	m_pRenderer->start();

	// load the state
	loadState();
}

void Engine::stop()
{
	// stop the managers
	InputManager::GetInstance()->stop();	
	StateManager::GetInstance()->stop();
	GraphicsManager::GetInstance()->stop();
	SoundManager::GetInstance()->stop();
	GUI::GUISystem::GetInstance()->DestroyGUI();
	EntityManager::GetInstance()->stop();

	// destroy the singletons
	InputManager::GetInstance()->DestroyInstance();
	StateManager::GetInstance()->DestroyInstance();
	Logger::GetInstance()->DestroyInstance();
	GraphicsManager::GetInstance()->DestroyInstance();
	SoundManager::GetInstance()->DestroyInstance();
	EntityManager::GetInstance()->DestroyInstance();
	WinTimer::GetInstance()->DestroyInstance();
	GUI::GUISystem::GetInstance()->DestroyInstance();
	AIEngine::GetInstance()->DestroyInstance();
	TextureManager::GetInstance()->DestroyInstance();

	// no need to delete the pointers we have because the managers will take of that for us
}

void Engine::loadState()
{
	// set the current state & scene
	m_pCurrentState = StateManager::GetInstance()->getCurrentState();

	assert(m_pCurrentState != NULL);
	// start the current state
	m_pCurrentState->start();
}

void Engine::update()
{
	if(!m_bDoExit)
	{
		m_pController->Update();
		m_pCurrentState->update();
	}
	else
		throw "EXIT_ENGINE";
}

void Engine::render()
{
	if(AnimateNextFrame(60.0f)) // lock the frame rate at 60fps
	{
		// update
		update();

		m_pRenderer->preRender();

		m_pCurrentState->render(m_pRenderer);
		
		// render the GUI
		GUI::GUISystem::GetInstance()->RenderPage();

		m_pRenderer->postRender();		
	}
	else
		Sleep(1);//TODO: Exception caught here need to solve....
}

void Engine::processEngineInput()
{

}
