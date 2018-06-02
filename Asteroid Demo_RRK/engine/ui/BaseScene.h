#ifndef __BASESCENE_H
#define __BASESCENE_H

#include <string>
#include "IScene.h"
#include "game/objects/IEntity.h"

// BaseScene Description
//
// BaseScene is an implementation of the IScene interface.
class BaseScene : public IScene
{
public:
	BaseScene(const char * name);
	virtual ~BaseScene();

	virtual void update();
	virtual void destroy();

	virtual void addEntity(IEntity *ent);
	//virtual void removeEntity(const char *name);
	//virtual void removeEntity(unsigned long entityId);

	//virtual void removeEntity(const char *name) = 0;
	//virtual void removeEntity(unsigned long entityId) = 0;
	// Get an entity using it's name, slow since it's comparing strings
	virtual IEntity * getEntity(const char *name);
	// If you've stored the HashedString you used when creating an entity you
	// can use it's hash value to get the entity. It should be faster since
	// it's comparing long types.
	virtual IEntity * getEntity(unsigned long entityId);
	
	virtual EntityList* getEntityListPointer();

	
	virtual bool removeEntity(const char *name);
	virtual bool removeEntity(unsigned long entityId);

protected:
	EntityList m_Entities;
	std::string m_Name;
};

#endif