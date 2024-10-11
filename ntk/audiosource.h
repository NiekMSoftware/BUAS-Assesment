#pragma once

class AudioSource
{
public:
	void Play(std::string id);
	void Pause();
	void Stop();
private:
	ALuint m_source;
};