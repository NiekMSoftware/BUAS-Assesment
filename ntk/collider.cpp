#include "precomp.h"
#include "collider.h"

Collider::Collider(Transform t, float w, float h, bool isTrigger = false)
	: transform(t), width(w), height(h), trigger(isTrigger)
{ }

// basic AABB collision detection.
bool Collider::IsColliding(const Collider & other, bool& isTriggerCollision) const
{
	// Initialize trigger collision to false
	isTriggerCollision = false;

	bool isColliding = (transform.x < other.transform.x + other.width &&
		transform.x + width > other.transform.x && 
		transform.y < other.transform.y + other.height &&
		transform.y + height > other.transform.y);

	// if colliding and either object is a trigger, set isTriggerCollision to true
	if (isColliding && (trigger || other.trigger))
	{
		isTriggerCollision = true;
		return false; // don't block movement, but still register collision
	}

	// if not a trigger, return the actual collision state.
	return isColliding;
}

void Collider::DrawCollider(Surface* screen)
{
	screen->Box(transform.x, transform.y, transform.x + width, transform.y + height, 0xff6969);
}