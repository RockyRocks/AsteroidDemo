#include "SoundManager.h"

SoundManager::SoundManager(void)
{
	m_pSound = NULL;
}

SoundManager::~SoundManager(void)
{
}

ISoundSystem * SoundManager::getSoundSystem() const
{
	return m_pSound;
}

void SoundManager::start()
{
#ifdef _WIN32
	m_pSound = new PCSound;
#endif

	assert(m_pSound != NULL);
	m_pSound->start();
	
}

void SoundManager::stop()
{
	m_pSound->stop();

	delete m_pSound;
	m_pSound = NULL;
}