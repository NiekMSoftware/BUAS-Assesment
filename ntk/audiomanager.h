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
	ALuint* RetrieveAudio(std::string id);

private:
	AudioManager() : al_device(nullptr), al_context(nullptr) { }

private:
	ALCdevice* al_device;
	ALCcontext* al_context;

	std::map<std::string, std::unique_ptr<ALuint>> m_audioCache;
};