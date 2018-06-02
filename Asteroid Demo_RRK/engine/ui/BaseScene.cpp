#include "BaseScene.h"

BaseScene::BaseScene(const char *name)
: m_Name(name)
{
}

BaseScene::~BaseScene()
{
}

EntityList * BaseScene::getEntityListPointer()
{
	return &m_Entities;
}

void BaseScene::addEntity(IEntity *ent)
{
	m_Entities.push_back(ent);
}

void BaseScene::destroy()
{
	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		IEntity *pEnt = (*it);
		++it;
		delete pEnt;
	}
	m_Entities.clear();
}

void BaseScene::update()
{
	// go through the list of entites, updating as we go
	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		if((*it)->isVisible()) // only update the entity if it's visible
		{
			(*it)->update();
		}
		++it;
	}
}

IEntity * BaseScene::getEntity(const char *name)
{
	IEntity *pEnt = NULL;

	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		if((*it)->getName().compare(name)==0)
		{
			pEnt = (*it);
			break;
		}
		++it;
	}

	return pEnt;
}
IEntity * BaseScene::getEntity(unsigned long entityId)
{
	IEntity *pEnt = NULL;

	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		if((*it)->getEntityId() == entityId)
		{
			pEnt = (*it);
			break;
		}
		++it;
	}

	return pEnt;
}

bool BaseScene::removeEntity(const char *name)
{
	return false;
}
bool BaseScene::removeEntity(unsigned long entityId)
{
	// technically, we aren't removing anything
	return false;
}

//void BaseScene::removeEntity(const char *name)
//{
//	EntityList::iterator it = m_Entities.begin();
//	while(it != m_Entities.end())
//	{
//		
//		++it;
//	}
//}
//void BaseScene::removeEntity(unsigned long entityId)
//{
//}