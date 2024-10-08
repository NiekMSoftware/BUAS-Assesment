#include "precomp.h"
#include "audiomanager.h"

AudioManager& AudioManager::Instance()
{
	static AudioManager instance;
	return instance;
}

void AudioManager::Init()
{
	// Open the default device
	al_device = alcOpenDevice(nullptr);
	if (!al_device)
	{
		std::cerr << "Failed to open OpenAL device.\n";
		return;
	}

	// Create and set the context
	al_context = alcCreateContext(al_device, nullptr);
	if (!al_context)
	{
		std::cerr << "Failed to create OpenGL context.\n";
	}

	alcMakeContextCurrent(al_context);
	printf("OpenAL initialized successfully.\n");
}

void AudioManager::ShutDown()
{
	// Clean up OpenAL
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(al_context);
	alcCloseDevice(al_device);
}

bool AudioManager::LoadSound(const string& fileName, ALuint& buffer)
{
	return false;
}

void AudioManager::PlaySound(ALuint& buffer)
{
}

void AudioManager::PlayMusic(ALuint& buffer)
{
}
