#ifndef __PCSOUNDSYSTEM_H
#define __PCOUSNDSYSTEM_H

#include <string>
#include "..\..\common\logger\Logger.h"
#include"ISoundSystem.h"
#include"SoundUtil.h"
#include "..\..\common\utils\Singleton.h"

using namespace std;

class PCSound : public ISoundSystem
{
public:
	PCSound();
	// initialise the sound api for platform
	void start();

	// stop the sound system, clear up pointers, etc.
	void stop();

	void stopAllSounds();
	// play a sound 
	void play(SoundID id);
	// stop a sound
	void stop(SoundID id);
	// pause a sound
	void pause(SoundID id);
	
	virtual void mute();

	
private:
	// load sounds
	void loadSounds();

	bool m_Mute;
	

	// list of sounds
		vector<SoundUtil>m_SoundUtil;
	// Paramaters

	
};

inline void PCSound::mute()
{
	m_Mute = !m_Mute;
}

#endif
