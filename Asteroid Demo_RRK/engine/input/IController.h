#ifndef __ICONTROLLER_H
#define __ICONTROLLER_H

enum Key;

typedef unsigned int UINT;
// IController Description
//
// Describes the functions necessary for input.
// The engine will 
class IController
{
public:
	virtual ~IController(){};

	virtual void Start()=0;

	virtual void Stop()=0;

	virtual bool KeyDown(Key key)=0;

	virtual bool KeyUP(Key key)=0;

	virtual void Update() = 0;

	virtual bool KeyPressed(int) = 0;

	virtual bool ActionKeysActive(UINT nAction, bool IsContinousKeyPress) = 0;
};
#endif

