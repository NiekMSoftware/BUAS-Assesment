#pragma once

class Player
{
public:
	Player(Sprite* sprite, float startX, float startY);
	Player(Sprite* sprite);

	void Tick(Surface* screen, float deltaTime);
	void Draw(Surface* screen);

	// input handling
	void KeyUp(int key);
	void KeyDown(int key);

	void SpawnAt(int tileX, int tileY);
public:
	Transform m_transform;
	Collider m_col;
	Input m_input;

private:
	Sprite* p_sprite;
};