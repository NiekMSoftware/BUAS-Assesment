#pragma once

class AudioSource
{
public:
	AudioSource();
	~AudioSource();

	// Basic audio playback
	void Play(std::string soundID);
	void Pause();
	void Stop();

private:
	ALuint m_source;
};