#include"PCSound.h"

#include "..\..\common\utils\Utils.h"

PCSound::PCSound()
{
	alutInit(0, NULL);
	m_Mute = false;
}
void PCSound::start()
{
	loadSounds();
}

void PCSound::stop()
{
	m_SoundUtil.clear();
}

void PCSound::play(SoundID id)
{
	if(!m_Mute)
	{
		if(id <= m_SoundUtil.size())
		{
			SoundUtil tempSoundUtil = m_SoundUtil.at(id);

			tempSoundUtil.PlaySound();
		}
		else
		{
			std::string s = "Cannot find sound file id to play: ";
			s.append(Utils::numberToString((const int)id));
			Logger::GetInstance()->printMsg(WARNING, s.c_str());
		}
	}
}


void PCSound::stopAllSounds()
{
	if(!m_Mute)
	{
		vector<SoundUtil>::iterator it;
		SoundUtil tempSoundUtil;
		for(it = m_SoundUtil.begin(); it!= m_SoundUtil.end(); ++it)
		{
			tempSoundUtil = *it;
			tempSoundUtil.StopSound();
		}
	}
}

void PCSound::stop(SoundID id)
{
	if(!m_Mute)
	{
		if(id <= m_SoundUtil.size())
		{
			SoundUtil tempSoundUtil = m_SoundUtil.at(id);

			//assert(tempSoundUtil != NULL);

			tempSoundUtil.StopSound();
		}
		else
		{
			std::string s = "Cannot find sound file id to stop: ";
			s.append(Utils::numberToString((const int)id));
			Logger::GetInstance()->printMsg(WARNING, s.c_str());
		}
	}
}

void PCSound::pause(SoundID id)
{
	
}

void PCSound::loadSounds()
{
	SoundUtil t0;
	if(!t0.InitializeSound("data\\music.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file music.wav");
	m_SoundUtil.push_back(t0);

	SoundUtil t1;
	if(!t1.InitializeSound("data\\bg1.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg1.wav");
	m_SoundUtil.push_back(t1);

	SoundUtil t2;
	if(!t2.InitializeSound("data\\bg2.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg2.wav");
	m_SoundUtil.push_back(t2);

	SoundUtil t3;
	if(!t3.InitializeSound("data\\bg3.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg3.wav");
	m_SoundUtil.push_back(t3);

	SoundUtil t4;
	if(!t4.InitializeSound("data\\bg4.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg3.wav");
	m_SoundUtil.push_back(t4);

	SoundUtil t5;
	if(!t5.InitializeSound("data\\bg5.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg4.wav");
	m_SoundUtil.push_back(t5);

	SoundUtil t6;
	if(!t6.InitializeSound("data\\bg6.wav", true))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg5.wav");
	m_SoundUtil.push_back(t6);

	SoundUtil t7;
	if(!t7.InitializeSound("data\\efire.wav", false))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg6.wav");
	m_SoundUtil.push_back(t7);

	SoundUtil t8;
	if(!t8.InitializeSound("data\\explosn.wav", false))
		Logger::GetInstance()->printMsg(WARNING, "Could not load sound file efire.wav");
	m_SoundUtil.push_back(t8);

	//Old version keeping it for a review later..
	//if(tempSoundUtil.InitializeSound("data\\bg1.wav", true))
	//{
	//	m_SoundUtil.push_back(tempSoundUtil);
	//	
	//	if(tempSoundUtil.InitializeSound("data\\efire.wav", false);
	//	m_SoundUtil.push_back(tempSoundUtil);
	//}
	//else
	//{
	//	Logger::GetInstance()->printMsg(WARNING, "Could not load sound file bg1.wav");
	//}
}