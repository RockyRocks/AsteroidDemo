#ifndef __ISOUNDSYSTEM_H
#define __ISOUNDSYSTEM_H

#include <vector>
#include <map>

typedef unsigned long SoundID;

/* Sound system interface that will manage the sound system */
/* Assign an id to the loaded sound to access it */
// Lifted this from my old Project
class ISoundSystem
{
public:
	virtual ~ISoundSystem() {};

	// initialize the sound api for platform
	virtual void start() = 0;

	// stop the sound system, clear up pointers, etc.
	virtual void stop() = 0;

	virtual void stopAllSounds() = 0;
	// play a sound 
	virtual void play(SoundID id) = 0;
	// stop a sound
	virtual void stop(SoundID id) = 0;
	// pause a sound
	virtual void pause(SoundID id) = 0;

	virtual void mute() = 0;
	
	// anything else we need to be concerned about?

private:
	// load sounds
	virtual void loadSounds() = 0;

	// list of sounds
};

#endif