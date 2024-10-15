#include "precomp.h"
#include "player.h"

Player::Player(Sprite* sprite, float startX, float startY) : p_sprite(sprite), m_transform(startX, startY)
{ }

Player::Player(Sprite* sprite) : p_sprite(sprite), m_transform(0, 0) 
{ }

void Player::Tick(Surface* screen, float deltaTime)
{ 
	/* Add logic to player */
	if (m_input.moveRight) {
		m_transform.Translate(100 * deltaTime, 0);
		if (m_transform.x > screen->width)
			m_transform.x = 0;
	}
	else if (m_input.moveLeft) {
		m_transform.Translate(-100 * deltaTime, 0);
		if (m_transform.x <= 0)
			m_transform.x = screen->width;
	}
}

void Player::Draw(Surface* screen)
{
	p_sprite->Draw(screen, static_cast<int>(m_transform.x), static_cast<int>(m_transform.y));
}

void Player::KeyUp(int key)
{
	m_input.HandleInput(key, false);
}

void Player::KeyDown(int key)
{
	m_input.HandleInput(key, true);
}

void Player::SpawnAt(int tileX, int tileY, int tileSize)
{
	m_transform.SetPosition(tileX * tileSize, tileY * tileSize);
}