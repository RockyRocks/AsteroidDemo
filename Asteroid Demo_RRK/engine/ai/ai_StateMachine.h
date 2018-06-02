#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <string>

#include "..\..\common\logger\Logger.h"
#include "..\objects\BaseEntity.h"
#include "ai_State.h"
#include <assert.h>

template<class entity_type>
class StateMachine
{

private:
	entity_type* eOwner;
	State<entity_type>* sCurrentState;
	State<entity_type>* sPreviousState;
	State<entity_type>* sGlobalState;
	State<entity_type>* sFlockingstate;
public:
	StateMachine(entity_type* owner):eOwner(owner),
		sCurrentState(NULL),
		sPreviousState(NULL),
		sGlobalState(NULL),
		sFlockingstate(NULL)
	{}

	virtual ~StateMachine(){}

	//use these methods to initialize the FSM
	void SetCurrentState(State<entity_type>* s){sCurrentState = s;}
	void SetGlobalState(State<entity_type>* s) {sGlobalState = s;}
	void SetPreviousState(State<entity_type>* s){sPreviousState = s;}
	void SetflockingState(State<entity_type>* s){sFlockingstate = s;}

	//call this to update the FSM
	void  Update()const
	{
		//BaseEntity *ent = (BaseEntity*) eOwner;
		//std::string s = "Updating state machine of: ";
		//s.append(ent->getName());
		//Logger::GetInstance()->printMsg(INFO, s.c_str());

		//if a global state exists, call its execute method, else do nothing
		if(sGlobalState)   sGlobalState->Execute(eOwner);

		//same for the current state
		if (sCurrentState) sCurrentState->Execute(eOwner);

		//same for the flocking state also
		if(sFlockingstate)sFlockingstate->Execute(eOwner);
	}

	//change to a new state
	void  ChangeState(State<entity_type>* sNewState)
	{
		assert(sNewState && 
			"<StateMachine::ChangeState>: trying to change to NULL state");

		if(sCurrentState)
		{
			//keep a record of the previous state
			sPreviousState=sCurrentState;

			//call the exit method of the existing state

			sCurrentState->Exit(eOwner);
		}

		//change state to the new state
		sCurrentState=sNewState;

		//call the entry method of the new state
		sCurrentState->Enter(eOwner);
	}

	//change state back to the previous state
	void  RevertToPreviousState()
	{
		ChangeState(sPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const State<entity_type>& st)const
	{
		return typeid(*sCurrentState) == typeid(st);
	}

	State<entity_type>*  CurrentState()  const{return sCurrentState;}
	State<entity_type>*  GlobalState()   const{return sGlobalState;}
	State<entity_type>*  PreviousState() const{return sPreviousState;}
	State<entity_type>*  flockingState() const{return sFlockingstate;}

};

#endif