#ifndef __STATE_H
#define __STATE_H


#include <vector>
#include <string>
#include "..\utils\HashedString.h"

class IRenderer;
class IScene;

class IState
{
public:
	IState();
	virtual ~IState();

	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update() = 0;
	virtual void processInput() = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void render(IRenderer *renderer) = 0;

	virtual const std::string getName() const = 0;
	virtual const unsigned long getId() const = 0;

	virtual void changeActiveness(bool b) = 0;
	virtual bool isActive() = 0;
};

#endif
