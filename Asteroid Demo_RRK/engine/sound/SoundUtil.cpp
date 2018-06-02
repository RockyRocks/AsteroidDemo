#include"SoundUtil.h"

//ALfloat SoundUtil::m_ListenerPos[]={0.0,0.0,4.0};
ALfloat SoundUtil::m_ListenerPos[]={0.0,0.0,0.0};
ALfloat SoundUtil::m_ListenerVel[]={0.0,0.0,0.0};
ALfloat	SoundUtil::m_ListenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};

ALfloat SoundUtil::m_SourcePos[]={ -2.0, 0.0, 0.0};
ALfloat SoundUtil::m_SourceVel[]={ 0.0, 0.0, 0.0};
SoundUtil::SoundUtil()
{
	m_bSoundLoaded = false;
	m_bSoundPlaying = false;
}

SoundUtil::~SoundUtil()
{
}

bool SoundUtil::InitializeSound(char *cFileName, bool loop)
{
	sprintf_s(m_soundFileName, sizeof(m_soundFileName)/sizeof(char), cFileName);
	return(CreateSound(loop));
}

bool SoundUtil::CreateSound(bool loop)
{
	
	ALfloat ListenerPos[]={0.0,0.0,4.0};
	ALfloat ListenerVel[]={0.0,0.0,0.0};
	ALfloat	ListenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};

	ALfloat SourcePos[]={ -2.0, 0.0, 0.0};
	ALfloat SourceVel[]={ 0.0, 0.0, 0.0};

	alListenerfv(AL_POSITION,ListenerPos);
	alListenerfv(AL_VELOCITY,ListenerVel);
	alListenerfv(AL_ORIENTATION,ListenerOri);
	
	if(alGetError() != AL_NO_ERROR) 
	{
		// Cannot Initialize Listener Parameters
		return false;
	}
	alGenBuffers(1, &m_Buffer);

	// Load the file
	alutLoadWAVFile((ALbyte *)m_soundFileName,&m_SoundFormat,&m_SoundData,
		&m_SoundFileSize,&m_SoundFreq,&m_Soundloop);
	alBufferData(m_Buffer,m_SoundFormat,m_SoundData,m_SoundFileSize,m_SoundFreq);
	alutUnloadWAV(m_SoundFormat,m_SoundData,m_SoundFileSize,m_SoundFreq);

	// Source
	if(alGetError() != AL_NO_ERROR) 
	{
		// Cannot Load the file
		return false;
	}

	alGenSources(1, &m_Source);

	if(alGetError() != AL_NO_ERROR) 
	{
		// Cannot Initialize Source Parameters
		return false;
	}

	alSourcef(m_Source,AL_PITCH,1.0f);
	alSourcef(m_Source,AL_GAIN,10.0f);
	alSourcefv(m_Source,AL_POSITION, SourcePos);
	alSourcefv(m_Source,AL_VELOCITY,SourceVel);
	alSourcei(m_Source,AL_BUFFER, m_Buffer);

	if(loop)
		alSourcei(m_Source,AL_LOOPING,AL_TRUE);
	
	m_bSoundLoaded = true;
	return true;
}


void SoundUtil::PlaySound()
{
	if(!m_bSoundPlaying)
	{
		alSourcePlay(m_Source);
		m_bSoundPlaying = true;
	}
}


void SoundUtil::StopSound()
{
	alSourceStop(m_Source);
}

void SoundUtil::PauseSound()
{

}