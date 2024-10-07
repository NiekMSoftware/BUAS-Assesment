#pragma once

class Player
{
public:
	Player(Sprite* sprite, float startX, float startY);
	Player(Sprite* sprite);

	void Tick(Surface* screen, float deltaTime);
	void Draw(Surface* screen);

	void SpawnAt(int tileX, int tileY, int tileSize);
public:
	Transform m_transform;
	Sprite* m_sprite;
};