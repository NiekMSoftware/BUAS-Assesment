#include "precomp.h"
#include "player.h"

Player::Player(Sprite* sprite, float startX, float startY) : m_sprite(sprite), m_transform(startX, startY)
{ }

Player::Player(Sprite* sprite) : m_sprite(sprite), m_transform(0, 0) 
{ }

void Player::Tick(Surface* screen, float deltaTime)
{ 
	/* Add logic to player */
	m_transform.Translate(100 * deltaTime, 0);
	if (m_transform.x > screen->width)
		m_transform.x = 0;
}

void Player::Draw(Surface* screen)
{
	m_sprite->Draw(screen, static_cast<int>(m_transform.x), static_cast<int>(m_transform.y));
}

void Player::SpawnAt(int tileX, int tileY, int tileSize)
{
	m_transform.SetPosition(tileX * tileSize, tileY * tileSize);
}