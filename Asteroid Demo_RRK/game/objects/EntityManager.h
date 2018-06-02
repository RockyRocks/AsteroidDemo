#ifndef __ENTITYMANAGER_H
#define __ENTITYMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "IEntity.h"
#include "..\..\common\utils\singleton.h"
#include "..\..\common\utils\Utils.h"

typedef std::vector<Vector2f> VertexList;

class EntityManager : public Singleton<EntityManager>
{
	friend Singleton<EntityManager>;

public:
	EntityManager();
	~EntityManager();

	void start();
	void stop();

	void registerEntity(IEntity *ent);
	void removeEntity(unsigned long entityId);
	IEntity * getEntity(unsigned long entityId);

	bool loadVertexFile(const char *file, VertexList *outVertexList);

	void setCurrentVertexInstance(unsigned int instance);

	VertexList * getVertexInstancePointer(unsigned int instance);
	VertexList * getCurrentVertexInstancePointer();
private:
	typedef std::pair<unsigned long, IEntity*> EntityMapEntry;
	typedef std::map<unsigned long, IEntity*> EntityMap;

	typedef std::vector<VertexList*> VertexInstances;

	EntityMap m_Entities;
	VertexInstances m_VertexInstances;
	VertexList * m_pCurrentInstance;
};

#endif
