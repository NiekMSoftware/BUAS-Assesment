#pragma once

class AudioManager
{
public:
	static AudioManager& Instance();

	void Init(); //< Initialize OpenAL
	void ShutDown(); //< Shutdown OpenAL

	bool LoadSound(const string& fileName, ALuint& buffer);
	void PlaySound(ALuint& buffer);
	// play sound that loops (music)
	void PlayMusic(ALuint& buffer);

private:
	AudioManager() = default;
	~AudioManager() = default;

	// prevent copy
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager& operator=(AudioManager&&) = delete;

private:
	ALCdevice* al_device;
	ALCcontext* al_context;
};