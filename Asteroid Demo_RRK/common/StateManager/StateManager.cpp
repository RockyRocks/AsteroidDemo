#include "StateManager.h"

StateManager::StateManager()
{
	m_pCurrentState = NULL;
}

StateManager::~StateManager()
{
}

void StateManager::stop()
{
	StateMap::iterator it = m_States.begin();
	while(it != m_States.end())
	{
		(*it).second->stop();
		delete (*it).second;
		++it;
	}

	m_States.clear();
}

void StateManager::addState(IState *state)
{
	unsigned long sid = state->getId();
	m_States[state->getId()] = state;
}
void StateManager::removeState(IState *state)
{
	StateMap::iterator it = m_States.find(state->getId());

	if(it != m_States.end())
	{
		m_States.erase(it);
	}
}
bool StateManager::makeCurrentState(const unsigned long sceneId)
{
	StateMap::iterator it = m_States.find(sceneId);

	if(it != m_States.end())
	{
		m_pCurrentState = it->second;
		return true;
	}
	else // state doesn't exist
		return false;
}

bool StateManager::makeCurrentState(const HashedString &stateName)
{
	StateMap::iterator it = m_States.find(stateName.getHashValue());

	if(it != m_States.end())
	{
		m_pCurrentState = it->second;
		return true;
	}
	else // state doesn't exist
		return false;
}
IState* StateManager::getCurrentState() const
{
	return m_pCurrentState;
}