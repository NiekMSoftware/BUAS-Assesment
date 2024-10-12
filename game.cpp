// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

AudioSource* jumpSoundSource;
AudioSource* musicSoundSource;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	auto& audioinstance = AudioManager::GetInstance();
	audioinstance.LoadAudioFile("assets/sfx/pog.wav", "music");
	audioinstance.LoadAudioFile("assets/sfx/jump.wav", "jump");

	jumpSoundSource = new AudioSource();
	musicSoundSource = new AudioSource();

	musicSoundSource->Play("music");
}

float timer = 0.0f;
// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	timer += deltaTime;
}

// -----------------------------------------------------------
// Main application render function - Executed once per frame
// -----------------------------------------------------------
void Game::Render()
{
	screen->Clear(0);
}