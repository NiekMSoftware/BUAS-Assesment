#include "precomp.h"
#include "player.h"

Player::Player(Sprite* sprite, float startX, float startY) : p_sprite(sprite), m_transform(startX, startY), m_col(m_transform, 32, 32, false)
{ }

Player::Player(Sprite* sprite) : p_sprite(sprite), m_transform(0, 0) , m_col(m_transform, 32, 32, false)
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

	// update collider's position
	m_col.transform.x = m_transform.x;
}

void Player::Draw(Surface* screen)
{
	p_sprite->Draw(screen, static_cast<int>(m_transform.x), static_cast<int>(m_transform.y));
	m_col.DrawCollider(screen);
}

void Player::KeyUp(int key)
{
	m_input.HandleInput(key, false);
}

void Player::KeyDown(int key)
{
	m_input.HandleInput(key, true);
}

void Player::SpawnAt(int tileX, int tileY)
{
	m_transform.SetPosition(tileX, tileY);
}