#pragma once

class GameObject
{
public:
	GameObject(const char* fileName, const char* id, int numFrames);

public:
	Sprite m_sprite;

	Transform m_transform;
	Collider m_collider;
};