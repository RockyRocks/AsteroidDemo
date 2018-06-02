#ifndef __INPUTMANAGER_H
#define __INPUTMANAGER_H

#include "..\..\common\logger\Logger.h"
#include "IController.h"
#include "PCInputcontroller.h"
#include "..\..\common\utils\Singleton.h"

// InputManager Description
//
// Used for assigning controllers to whoever needs it?
class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;

public:
	bool start();
	void stop();

	IController * getController() const;

private:
	InputManager();
	~InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager);


	IController * m_Controller;
	// list of controllers???
};

#endif