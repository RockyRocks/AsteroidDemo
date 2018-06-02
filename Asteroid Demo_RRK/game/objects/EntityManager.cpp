#include "EntityManager.h"

EntityManager::EntityManager(void)
{
}

EntityManager::~EntityManager(void)
{
	m_Entities.clear();
}

void EntityManager::start()
{
	VertexList *pVList = new VertexList;
	loadVertexFile("data\\enemy1.txt", pVList);
	m_VertexInstances.push_back(pVList);

	// set the current instance to the enemy1
	m_pCurrentInstance = pVList;

	pVList = new VertexList;
	loadVertexFile("data\\enemy2.txt", pVList);
	m_VertexInstances.push_back(pVList);
	
	pVList = new VertexList;
	loadVertexFile("data\\enemy3.txt", pVList);
	m_VertexInstances.push_back(pVList);
	
	pVList = new VertexList;
	loadVertexFile("data\\enemy4.txt", pVList);
	m_VertexInstances.push_back(pVList);
	
	pVList = new VertexList;
	loadVertexFile("data\\enemy5.txt", pVList);
	m_VertexInstances.push_back(pVList);
	
	pVList = new VertexList;
	loadVertexFile("data\\enemy6.txt", pVList);
	m_VertexInstances.push_back(pVList);
}
void EntityManager::stop()
{
	VertexInstances::iterator it = m_VertexInstances.begin();
	while(it != m_VertexInstances.end())
	{
		delete (*it);
		++it;
	}
	m_VertexInstances.clear();
}

VertexList * EntityManager::getCurrentVertexInstancePointer()
{
	return m_pCurrentInstance;
}

void EntityManager::registerEntity(IEntity *ent)
{
	assert(ent != NULL);
	m_Entities.insert(EntityMapEntry(ent->getEntityId(), ent));
}
void EntityManager::removeEntity(unsigned long entityId)
{
	assert(entityId != 0);
	EntityMap::iterator it = m_Entities.begin();

	if(it != m_Entities.end())
		m_Entities.erase(it);
}

IEntity * EntityManager::getEntity(unsigned long entityId)
{
	assert(entityId != 0);
	EntityMap::iterator it = m_Entities.find(entityId);
	
	if(it != m_Entities.end())
		return (*it).second;
	else
		return NULL;
}

bool EntityManager::loadVertexFile(const char *file, VertexList *outVertexList)
{
	std::ifstream in(file);
	std::string inLine;

	if(in.is_open())
	{
		while(getline(in, inLine))
		{
			std::istringstream line(inLine);
			std::string s;

			if(inLine[0] == 'v')
			{
					// process vertices
					float x,y;
					line >> s >> x >> y;
					outVertexList->push_back(Vector2f(x,y));
			}
		}
		in.close();

		return true;
	}
	else
	{
		in.close();
		return false;
	}
}

VertexList * EntityManager::getVertexInstancePointer(unsigned int instance)
{
	if(instance < m_VertexInstances.size())
		return m_VertexInstances.at(instance);
	//else
	//{
	//	std::string s = "[EntityManager] - Couldn't get your vertex list ";
	//	s.append(Utils::numberToString((const int)instance));
	//	Logger::GetInstance()->printMsg(WARNING, s.c_str());
	//}
	return 0;
}

void EntityManager::setCurrentVertexInstance(unsigned int instance)
{
	if(instance < m_VertexInstances.size())
	//{
		m_pCurrentInstance = m_VertexInstances.at(instance);
	//}
	//else
	//{
	//	std::string s = "[EntityManager] - Couldn't set current vertex list ";
	//	s.append(Utils::numberToString((const int)instance));
	//	Logger::GetInstance()->printMsg(WARNING, s.c_str());
	//}
}
