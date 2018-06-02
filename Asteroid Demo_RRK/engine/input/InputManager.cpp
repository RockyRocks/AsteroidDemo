#include "InputManager.h"

InputManager::InputManager()
{
	m_Controller = NULL;
}

InputManager::~InputManager()
{
	if(m_Controller != NULL)
		delete m_Controller;
}

bool InputManager::start()
{
	// create a new controller interface
	if(m_Controller == NULL)
	{
		m_Controller = new PCInputcontroller();
		// start it
		m_Controller->Start();

		return true;
	}
	else
	{
		// output to log if controller cannot be made
		Logger::GetInstance()->printMsg(ERRORLOG, " - [InputManager] - Cannot create controller");
		return false;
	}
}

void InputManager::stop()
{
	if(m_Controller != NULL)
	{
		// stop the controller
		m_Controller->Stop();
	
		// delete
		delete m_Controller;
	}
	m_Controller = NULL;
}

IController * InputManager::getController() const
{
	return m_Controller;
}