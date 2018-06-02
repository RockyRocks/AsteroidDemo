#ifndef __BASESTATE_H
#define __BASESTATE_H

#include <vector>
#include "istate.h"
#include "..\..\engine\engine.h"
#include "..\utils\HashedString.h"
#include "PlayerScore.h"

typedef std::vector<IEntity*> EntityList;

// BaseState Description
//
// An abstract class partially implementing the IState interface
// Each state will have to define it's own start method, typically used for
// creating scenes & entities as well as setting up events for that particular
// state.
// The stop method is used for cleaning up, deleting pointers, etc. Stop is usually
// called when quitting the engine/game.
// The update method is for updating the scene/entites/events & any other data in the
// engine.
// The processInput method allows the state to customise the input from the IController
// interface. The action keys are defined in "engine\input\PCInputcontroller.h"
class BaseState : public IState
{
public:
	BaseState(const char * name) : m_NameId(HashedString(name)) {}
	virtual ~BaseState(void);

	// Let sub-classes implement these
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update() = 0;

	virtual const std::string getName() const { return m_NameId.getStr(); }
	virtual const unsigned long getId() const { return m_NameId.getHashValue(); }

	// sub-classes will have to handle their own input from controller
	virtual void processInput() = 0;
	// loads the state
	virtual void load() = 0;
	// unload the state
	virtual void unload() = 0;

	// a base state cannot render anything
	virtual void render(IRenderer *renderer);

	virtual void changeActiveness(bool b);
	virtual bool isActive();
	static void SetPlayer1Score(const int &score, const int &round);
	static void SetPlayer2Score(const int &score, const int &round);


protected:
	HashedString m_NameId;
	//IScene * m_pScene;	
	IController * m_pController;
	ISoundSystem * m_pSoundsystem;

	bool m_bHasAlreadyStarted;
	bool m_bIsActive;
	
	static PlayerScore m_Player1;
	static PlayerScore m_Player2;

	static int m_nGameMode;  // mode = 0 -> normal mode, 1 -> Hard mode;

	EntityList m_Entities;
};

inline BaseState::~BaseState()
{
	// delete the entities
	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		delete (*it);
		++it;
	}
}

inline void BaseState::render(IRenderer *renderer)
{
	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		(*it)->render(renderer);
		++it;
	}
}

inline void BaseState::changeActiveness(bool b)
{
	m_bIsActive = b;
}

inline bool BaseState::isActive()
{
	return m_bIsActive;
}
//int BaseState::m_nGameMode = 0;

inline void BaseState::SetPlayer1Score(const int &score, const int &round)
{
	m_Player1.SetScore(score);
	m_Player1.SetRound(round);
}

inline void BaseState::SetPlayer2Score(const int &score, const int &round)
{
	m_Player2.SetScore(score);
	m_Player2.SetRound(round);
}

#endif