#pragma once

class GameObject
{
public:
	GameObject(const char* fileName, const char* id, int nf);

	// methods
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(Surface* screen) = 0;

	// retrieve components
	const Sprite& getSprite();
	const Transform& getTransform();
	const Collider& getCollider();

protected:
	Sprite m_sprite;

	Transform m_transform;
	Collider m_collider;
};