#include "precomp.h"
#include "audiomanager.h"

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

AudioManager& AudioManager::GetInstance()
{
	static AudioManager instance;
	return instance;
}

// turn off optimization for this specific section
#pragma optimize("", off)
bool AudioManager::InitializeOpenAL()
{
	// open default device
	al_device = alcOpenDevice(nullptr);
	if (!al_device)
	{
		std::cerr << "AudioManager::InitializeOpenAL() - Failed to open audio device\n";
		return false;
	}

	// create audio context from device
	al_context = alcCreateContext(al_device, nullptr);
	if (!al_context)
	{
		std::cerr << "AudioManager::InitializeOpenAL() - Failed to create context\n";
		alcCloseDevice(al_device);
		return false;
	}

	// set current context
	if (!alcMakeContextCurrent(al_context))
	{
		std::cerr << "AudioManager::InitializeOpenAL() - Failed to set context as current\n";
		alcDestroyContext(al_context);
		alcCloseDevice(al_device);
		return false;
	}

	// everything went good
	return true;
}

void AudioManager::ShutdownOpenAL()
{
	// clear current context
	alcMakeContextCurrent(nullptr);

	// destroy context and device
	if (al_context && al_device)
	{
		alcDestroyContext(al_context);
		al_context = nullptr;

		alcCloseDevice(al_device);
		al_device = nullptr;
	}
}

// Done with a bit of help from Chat GPT, wasn't all too sure how to implement Dr Wav into it.
void AudioManager::LoadAudioFile(std::string filePath, std::string id)
{
	drwav wav;
	if (!drwav_init_file(&wav, filePath.c_str(), nullptr))
	{
		std::cerr << "AudioManager::LoadAudioFile() - Failed to load WAV file: " << filePath << '\n';
		return;
	}

	// read the audio data
	size_t dataSize = wav.totalPCMFrameCount * wav.channels * sizeof(drwav_int16);
	std::vector<drwav_int16> audioData(wav.totalPCMFrameCount * wav.channels);
	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, audioData.data());

	// genereate OpenAL buffer
	ALuint buffer;
	alGenBuffers(1, &buffer);

	// determine OpenAL format
	ALenum format;
	if (wav.channels == 1)
		format = AL_FORMAT_MONO16;
	else if (wav.channels == 2)
		format = AL_FORMAT_STEREO16;
	else
	{
		std::cerr << "AudioManager::LoadAudioFile() - Unsupoorted number of channels: " << wav.channels << '\n';
		drwav_uninit(&wav);
		return;
	}

	// buffer the audio data into OpenAL
	alBufferData(buffer, format, audioData.data(), dataSize, wav.sampleRate);

	// cache the buffer in the suond cache
	m_audioCache[id] = std::make_unique<ALuint>(buffer);

	// Clean up dr_wav resources
	drwav_uninit(&wav);
}

ALuint* AudioManager::RetrieveAudioBuffer(std::string id)
{
	// find the sound with id
	auto itr = m_audioCache.find(id);
	if (itr == m_audioCache.end())
	{
		std::cerr << "AudioManager::RetrieveAudioBuffer() - Unable to find a sound with id: " << id << '\n';
		return nullptr;
	}

	// retrieve the buffer
	ALuint buffer = *(itr->second);
	return &buffer;
}
#pragma optimize("", on) // turn it back on

void AudioManager::SetGroupVolume(AudioGroup group, float volume)
{
	if (group == Master)
	{
		m_masterVolume = volume;
		for (auto& pair : m_audioGroups)
		{
			for (ALuint source : pair.second.sources)
			{
				float adjustedVolume = pair.second.volume * m_masterVolume;
				alSourcef(source, AL_GAIN, adjustedVolume);
			}
		}
	}
	else
	{
		m_audioGroups[group].volume = volume;
		for (auto source : m_audioGroups[group].sources)
		{
			float adjustedVolume = volume * m_masterVolume;
			alSourcef(source, AL_GAIN, adjustedVolume);
		}
	}
}

float AudioManager::GetGroupVolume(AudioGroup group) const
{
	if (group == Master)
		return m_masterVolume;

	return m_audioGroups.at(group).volume;
}

void AudioManager::AssignGroup(ALuint source, AudioGroup group)
{
	// remove the source from any previous group it may have been in
	for (auto& pair : m_audioGroups)
	{
		auto& sources = pair.second.sources;
		sources.erase(std::remove(sources.begin(), sources.end(), source), sources.end());
	}

	// add the source to a group
	m_audioGroups[group].sources.push_back(source);

	// set the initial volume for the source based on the group and master volume
	float adjustedVolume = m_audioGroups[group].volume * m_masterVolume;
	alSourcef(source, AL_GAIN, adjustedVolume);
}
