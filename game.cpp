// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

AudioSource* jumpSoundSource;
AudioSource* musicSoundSource;

float funnyValue = 1.0f;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	auto& audioinstance = AudioManager::GetInstance();
	audioinstance.LoadAudioFile("assets/sfx/pog.wav", "music");
	audioinstance.LoadAudioFile("assets/sfx/jump.wav", "jump");

	audioinstance.SetGroupVolume(AudioManager::Music, funnyValue);
	audioinstance.SetGroupVolume(AudioManager::Sfx, 0.7f);
	audioinstance.SetGroupVolume(AudioManager::Master, 0.8f);

	// instantiate the audio sources
	jumpSoundSource = new AudioSource(AudioManager::Sfx);
	musicSoundSource = new AudioSource(AudioManager::Music);

	musicSoundSource->Play("music");
}

float timer = 0.0f;
const float epsilon = 0.01f;
// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	static bool IsDecreasing = true;
	timer += deltaTime;

	// derease audio after 3 seconds
	if (timer >= 1.5f && IsDecreasing)
	{
		funnyValue -= deltaTime;

		if (fabs(funnyValue) < epsilon)
		{
			timer = 0.0f;
			funnyValue = 0.0f;
			IsDecreasing = false;
			jumpSoundSource->Play("jump");

		}
	}
	else if (!IsDecreasing)
	{
		funnyValue += deltaTime;

		if (funnyValue >= 1.f)
		{
			funnyValue = 1.0f;
			IsDecreasing = true;
		}
	}

	//printf("funny value: %f\n", funnyValue);
	AudioManager::GetInstance().SetGroupVolume(AudioManager::Music, funnyValue);
}

// -----------------------------------------------------------
// Main application render function - Executed once per frame
// -----------------------------------------------------------
void Game::Render()
{
	screen->Clear(0);
}