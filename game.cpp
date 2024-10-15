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
	ResourceHolder& rhinstance = ResourceHolder::GetInstance();
	rhinstance.LoadSprite("player", "assets/playership.png", 9);
	p_player = new Player(rhinstance.GetSprite("player"));

	tileMap = new TileMap("assets/nc2tiles.png");
	tileMap->LoadJSONMap("assets/maps/test.json");
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	p_player->Tick(screen, deltaTime);
}

// -----------------------------------------------------------
// Main application render function - Executed once per frame
// -----------------------------------------------------------
void Game::Render()
{
	screen->Clear(0);
	tileMap->DrawMap(screen);
	p_player->Draw(screen);
}