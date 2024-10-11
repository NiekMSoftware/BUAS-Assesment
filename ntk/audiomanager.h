#pragma once

/**
* @class AudioManager
* @brief Manages OpenAL and different audio-functions like adjusting volume on groups, loading of files and grouping audio.
*
*/
class AudioManager
{
public:
	enum AudioGroup
	{
		Master,
		Music,
		Sfx
	};

public:
	static AudioManager& GetInstance();

	// OpenAL handling
	bool InitializeOpenAL();
	void ShutdownOpenAL();

	void LoadAudioFile(std::string filePath, std::string id);

private:
	AudioManager() = default;

private:
	ALCdevice* al_device;
	ALCcontext* al_context;

	std::unordered_map<std::string, ALuint> m_soundMap;
};