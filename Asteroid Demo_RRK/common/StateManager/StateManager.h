#ifndef __STATEMANAGER_H
#define __STATEMANAGER_H

#include <map>
#include "IState.h"
#include "..\utils\HashedString.h"
#include "..\utils\Singleton.h"

typedef std::map<unsigned long, IState*> StateMap;
// StateManager Description
//
// A state manager to handle the set of states in the game.
// Users will have to implement their own state based on the IState interface
// and then add them to the state manager for use by the engine
class StateManager : public Singleton<StateManager>
{
	friend Singleton<StateManager>;

public:
	void stop();
	void addState(IState *state);
	void removeState(IState *state);

	bool makeCurrentState(const unsigned long sceneId);
	bool makeCurrentState(const HashedString &stateName);
	IState* getCurrentState() const;

private:
	StateManager();
	~StateManager();
	StateManager(const StateManager&);
	StateManager& operator=(const StateManager);

	StateMap m_States;
	IState *m_pCurrentState;
};

#endif