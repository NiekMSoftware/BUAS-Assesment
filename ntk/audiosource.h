#pragma once

// had to include audio manager header file to get the enum
#include "audiomanager.h" 

class AudioSource
{
public:
	AudioSource(AudioManager::AudioGroup audioGroup);
	~AudioSource();

	// Basic audio playback
	void Play(std::string soundID);
	void Pause();
	void Stop();

private:
	ALuint m_source;
};