#include "precomp.h"
#include "audiomanager.h"

AudioManager& AudioManager::GetInstance()
{
	static AudioManager instance;
	return instance;
}

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

void AudioManager::LoadAudioFile(std::string filePath, std::string id)
{
}