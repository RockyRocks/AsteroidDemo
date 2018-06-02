#include "AIEngine.h"

AIEngine::AIEngine(void)
{
}

AIEngine::~AIEngine(void)
{
}

IEntity* AIEngine::getRandomPlayer()
{
	m_RNG.randomise();

	// get a random number, clamped to the amount of players in play
	float r = (m_RNG.random() * m_Players.size()) - 1;

	if(r < 0.0)
		r = 0.0;

	int p = (int)r; // round it up

	return m_Players.at(p);
}

