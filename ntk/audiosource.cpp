#include "precomp.h"
#include "audiosource.h"

AudioSource::AudioSource() : m_source(0)
{
	alGenSources(1, &m_source);
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &m_source);
}

void AudioSource::Play(std::string soundID)
{
	ALuint* buffer = AudioManager::GetInstance().RetrieveAudioBuffer(soundID);
	if (buffer != 0) {
		alSourcei(m_source, AL_BUFFER, *buffer);
		alSourcePlay(m_source);
	}
	else {
		std::cerr << "Sound ID " << soundID << " not found in AudioManager.\n";
	}
}

void AudioSource::Pause()
{
	alSourcePause(m_source);
}

void AudioSource::Stop()
{
	alSourceStop(m_source);
}
