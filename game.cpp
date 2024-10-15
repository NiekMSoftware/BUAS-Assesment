// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

TileMap* tileMap;
Player* enemy;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{ 
	ResourceHolder& rhinstance = ResourceHolder::GetInstance();
	rhinstance.LoadSprite("player", "assets/playership.png", 9);
	p_player = new Player(rhinstance.GetSprite("player"));
	enemy = new Player(rhinstance.GetSprite("player"), 100, 0);
	enemy->m_col.trigger = true;

	tileMap = new TileMap("assets/nc2tiles.png");
	tileMap->LoadJSONMap("assets/maps/test2.json");
}

// this could activate something
bool isTriggerCollision = false;
float timer = 0;
// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	p_player->Tick(screen, deltaTime);

	if (p_player->m_col.IsColliding(enemy->m_col, isTriggerCollision))
	{
		if (p_player->m_input.moveRight)  // stop right movement
			p_player->m_transform = enemy->m_col.transform.x - p_player->m_col.width;
		else if (p_player->m_input.moveLeft)  // stop left movement
			p_player->m_transform = enemy->m_col.transform.x + enemy->m_col.width;
	}
	else if (isTriggerCollision)
	{
		timer += deltaTime;

		// play a timer that goes off every .5 seconds.
		if (timer >= .5f)
		{
			printf("TRIGGER DETECTED, PASSING THROUGH!\n");
			timer = 0.0f;
		}
	}
}

// -----------------------------------------------------------
// Main application render function - Executed once per frame
// -----------------------------------------------------------
void Game::Render()
{
	screen->Clear(0);
	tileMap->DrawMap(screen);
	p_player->Draw(screen);
	enemy->Draw(screen);
}