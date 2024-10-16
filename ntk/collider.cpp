#include "precomp.h"
#include "collider.h"

Collider::Collider(Transform t, float w, float h, bool isTrigger = false)
	: m_transform(t), width(w), height(h), trigger(isTrigger)
{ }

// basic AABB collision detection.
bool Collider::IsColliding(const Collider & other, bool& isTriggerCollision) const
{
	// Initialize trigger collision to false
	isTriggerCollision = false;

	bool isColliding = (m_transform.position.x < other.m_transform.position.x + other.width &&
		m_transform.position.x + width > other.m_transform.position.x &&
		m_transform.position.y < other.m_transform.position.y + other.height &&
		m_transform.position.y + height > other.m_transform.position.y);

	// if colliding and either object is a trigger, set isTriggerCollision to true
	if (isColliding && (trigger || other.trigger))
	{
		isTriggerCollision = true;
		return false; // don't block movement, but still register collision
	}

	// if not a trigger, return the actual collision state.
	return isColliding;
}

void Collider::DrawCollider(Surface* screen) const
{
	screen->Box(m_transform.position.x, m_transform.position.y, 
		m_transform.position.x + width, m_transform.position.y + height, 0xff6969);
}