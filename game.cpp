// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

TileMap* tileMap;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	tileMap = new TileMap("assets/nc2tiles.png", 1, 1, 1);
	tileMap->LoadMap("assets/maps/map.txt");
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float /* deltaTime */ )
{
	screen->Clear(0);

	tileMap->DrawMap(screen, 0, 0);
}