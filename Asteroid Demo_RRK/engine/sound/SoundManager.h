#ifndef __SOUNDMANAGER_H
#define __SOUNDMANAGER_H

#include "ISoundSystem.h"
#include "PCSound.h"
#include "..\..\common\utils\Singleton.h"

// SoundManager Description
//
// Manages the sound system pointers for the engine
class SoundManager : public Singleton<SoundManager>
{
	friend Singleton<SoundManager>;

public:
	ISoundSystem * m_pSound;

	void start();
	void stop();

	// Get a sound system. DO NOT DELETE THE POINTER!!!
	ISoundSystem * getSoundSystem() const;

private:
	SoundManager(void);
	~SoundManager(void);
	SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager);
};

#endif
