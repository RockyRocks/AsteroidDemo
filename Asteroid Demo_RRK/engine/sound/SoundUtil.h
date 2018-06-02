#pragma once
//Define the OPenAL
#pragma warning(disable : 4996)
#include<iostream>
#include <al.h>
#include <alc.h>
#include <alut.h>

typedef unsigned long SoundID;

using namespace std;

class SoundUtil
{
	public:
		SoundUtil();
		~SoundUtil();
		bool InitializeSound(char *cFileName, bool loop);
		void PlaySound();
		void StopSound();
		void PauseSound();

	private:
		SoundID m_SoundId;

		ALuint		m_Buffer;
		ALuint		m_Source;
		ALuint		m_environment;

		ALboolean	m_Soundloop;
		ALsizei		m_SoundFileSize;
		ALsizei		m_SoundFreq;
		ALenum 		m_SoundFormat;
		ALvoid 		*m_SoundData;

		static ALfloat		m_ListenerPos[];
		static ALfloat		m_ListenerVel[];
		static ALfloat		m_ListenerOri[];

		static ALfloat		m_SourcePos[];
		static ALfloat		m_SourceVel[];

		char	    m_soundFileName[100];
		bool		m_bSoundLoaded;
		bool		m_bSoundPlaying;
		bool		CreateSound(bool loop);
		

};