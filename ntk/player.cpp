#include "precomp.h"
#include "player.h"

Player::Player(const char* fileName, int nf)
	: GameObject(fileName, "player", nf)
{ }

void Player::Init()
{
	/* 
	  Initialize related player things in here 
	  e.g. player max steps, health etc. 
	*/
}

void Player::Update(float deltaTime)
{
	
}

void Player::Draw(Surface* screen)
{
	m_sprite->Draw(screen, 0, 0);

#ifdef _DEBUG
	m_collider.DrawCollider(screen);
#endif
}