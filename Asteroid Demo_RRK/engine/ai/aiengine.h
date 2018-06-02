#ifndef __AIENGINE_H
#define __AIENGINE_H

#include <vector>
#include "..\..\common\utils\Random.h"
#include "..\..\common\utils\Mathlib.h"
#include "..\..\common\utils\singleton.h"

using namespace MathLib;

class IEntity;

typedef std::vector<IEntity*> TargetList;
typedef std::vector<IEntity*> PlayerList;

class AIEngine : public Singleton<AIEngine>
{
	friend Singleton<AIEngine>;

public:
	void start();

	Vector2f createExitPoint();

	void addTarget(IEntity *pTarget);
	void addPlayer(IEntity *pPlayer);	

	IEntity* getTarget(unsigned int target);
	IEntity* getPlayer(unsigned int player);

	const unsigned int getNumPlayers() const;
	const unsigned int getNumTargets() const;

	const TargetList* getTargetList() const;
	const PlayerList* getPlayerList() const;

	IEntity* getRandomPlayer();
private:
	AIEngine(void);
	~AIEngine(void);
	AIEngine(const AIEngine&);
	AIEngine& operator=(const AIEngine);

	TargetList m_Targets;
	PlayerList m_Players;

	Random m_RNG;
};

inline void AIEngine::start()
{
	// just start to initialize the pointer
	// for better 

}

inline void AIEngine::addTarget(IEntity *pTarget)
{
	m_Targets.push_back(pTarget);
}
inline void AIEngine::addPlayer(IEntity *pPlayer)
{
	m_Players.push_back(pPlayer);
}
inline IEntity* AIEngine::getTarget(unsigned int target)
{
	if(target < m_Targets.size())
		return m_Targets.at(target);
	else
		return NULL;
}
inline IEntity* AIEngine::getPlayer(unsigned int player)
{
	if(player < m_Players.size())
		return m_Players.at(player);
	else
		return NULL;
}
inline const unsigned int AIEngine::getNumPlayers() const
{
	return m_Players.size();
}
inline const unsigned int AIEngine::getNumTargets() const
{
	return m_Targets.size();
}

inline const TargetList* AIEngine::getTargetList() const
{
	return &m_Targets;
}
inline const PlayerList* AIEngine::getPlayerList() const
{
	return &m_Players;
}

#endif