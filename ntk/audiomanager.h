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

	// Disable copying
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager& operator=(AudioManager&&) = delete;

	// OpenAL handling
	bool InitializeOpenAL();
	void ShutdownOpenAL();

	// Audio functions
	void LoadAudioFile(std::string filePath, std::string id);
	ALuint* RetrieveAudioBuffer(std::string id);

	// Managing groups
	void SetGroupVolume(AudioGroup group, float volume);
	float GetGroupVolume(AudioGroup group) const;
	void AssignGroup(ALuint source, AudioGroup group);

private:
	struct AudioGroupData
	{
		float volume = 1.0f;
		std::vector<ALuint> sources;
	};

	AudioManager() : al_device(nullptr), al_context(nullptr), m_masterVolume(1.0f) { }

private:
	std::map<AudioGroup, AudioGroupData> m_audioGroups;

	ALCdevice* al_device;
	ALCcontext* al_context;

	std::map<std::string, std::unique_ptr<ALuint>> m_audioCache;
	float m_masterVolume;
};