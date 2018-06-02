#ifndef __ISCENE_H
#define __ISCENE_H

#include <vector>
#include <algorithm>
#include "../Asteroid Demo_RRK/game/objects/IEntity.h"

class IRenderer;

typedef std::vector<IEntity*> EntityList;

// IScene Description
//
// Scene Interface for implementing scenes. A scene is a description of 
class IScene
{
public:
	IScene() {}
	virtual ~IScene() {}
	virtual void update(float dt) = 0;
	virtual void render(IRenderer *renderer) = 0;
	
	// perform cleanup
	virtual void destroy() = 0;

	virtual void addEntity(IEntity *ent) = 0;
	//virtual void removeEntity(const char *name) = 0;
	//virtual void removeEntity(unsigned long entityId) = 0;
	// Get an entity using it's name, slow!!
	virtual IEntity * getEntity(const char *name) = 0;
	// If you've stored the HashedString you used when creating an entity you
	// can use it's hash value to get the entity. This is faster than using strings.
	virtual IEntity * getEntity(unsigned long entityId) = 0;
	virtual EntityList* getEntityListPointer() = 0;

	virtual bool removeEntity(const char *name) = 0;
	virtual bool removeEntity(unsigned long entityId) = 0;
};

#endif