// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	auto& audioinstance = AudioManager::GetInstance();
	audioinstance.LoadAudioFile("assets/sfx/pog.wav", "test");

    // Get the buffer ID from the cache to play the sound
    auto it = audioinstance.m_soundCache.find("test");
    if (it != audioinstance.m_soundCache.end()) {
        ALuint buffer = *(it->second);  // Get the buffer ID
        ALuint source;
        alGenSources(1, &source);  // Generate a sound source

        // Attach the buffer to the source
        alSourcei(source, AL_BUFFER, buffer);

        // Play the sound
        alSourcePlay(source);

        ALint sourceState;
        alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
        if (sourceState != AL_PLAYING) {
            std::cerr << "Sound source is not playing!\n";
        }
    }
    else {
        std::cerr << "Failed to find the loaded sound." << std::endl;
    }
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{

}

// -----------------------------------------------------------
// Main application render function - Executed once per frame
// -----------------------------------------------------------
void Game::Render()
{
	screen->Clear(0);
}