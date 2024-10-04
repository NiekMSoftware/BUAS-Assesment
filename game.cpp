// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

#define SPRITESIZE 32

Surface tiles("assets/nc2tiles.png");
char tileMap[5][30] = 
{
	"kc kc kc kc kc kc kc kc kc kc",
	"kcXfb fb fbXkcXkcXkcXkc kc kc",
	"kcXfb fb fb fb fbXkcXkc kc kc",
	"kcXlcXlcXfb fb fbXkcXkc kc kc",
	"kcXkcXkcXlcXlcXlcXkcXkc kc kc"
};

TileMap* tMap;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	tMap = new TileMap("assets/nc2tiles.png", 10, 5);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float /* deltaTime */ )
{
	screen->Clear(0);

	int tileSize = 32;

	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 10; x++)
		{
			int tx = tileMap[y][x * 3] - 'a';
			int ty = tileMap[y][x * 3 + 1] - 'a';
			tMap->DrawTile(tx, ty, screen, x * tileSize, y * tileSize);
		}
}