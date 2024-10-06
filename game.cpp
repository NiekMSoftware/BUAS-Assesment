// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

TileMap* tMap;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	auto& resourceHolder = ResourceHolder::GetInstance();

	resourceHolder.LoadTileMap("test-level", "assets/nc2tiles.png");

	tMap = resourceHolder.GetTileMap("test-level");
	tMap->LoadMap("assets/maps/map.txt");
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float /* deltaTime */ )
{
	screen->Clear(0);
	tMap->DrawMap(screen);
}