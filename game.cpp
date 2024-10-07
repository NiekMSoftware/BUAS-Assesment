// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

TileMap* tMap;
Player* mPlayer;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	auto& resourceHolder = ResourceHolder::GetInstance();

	resourceHolder.LoadTileMap("test-level", "assets/nc2tiles.png");
	resourceHolder.LoadSprite("player", "assets/playership.png", 9);

	tMap = resourceHolder.GetTileMap("test-level");
	tMap->LoadMap("assets/maps/map.txt");

	auto playerSprite = resourceHolder.GetSprite("player");
	mPlayer = new Player(playerSprite, 0, 0);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	mPlayer->Tick(screen, deltaTime);
}

// -----------------------------------------------------------
// Main application render function - Executed once per frame
// -----------------------------------------------------------
void Game::Render()
{
	screen->Clear(0);
	tMap->DrawMap(screen);
	mPlayer->Draw(screen);
}