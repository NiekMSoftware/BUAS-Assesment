#include "precomp.h"
#include "audiosource.h"

void AudioSource::Play(std::string id)
{
	ALuint* buffer = AudioManager::GetInstance().RetrieveAudioBuffer(id);

	alGenSources(1, &m_source);
	alSourcei(m_source, AL_BUFFER, *buffer);

	alSourcePlay(m_source);
}