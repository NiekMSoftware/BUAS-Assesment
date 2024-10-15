#include "precomp.h"
#include "collider.h"

Collider::Collider(Transform t, float w, float h, bool isTrigger = false)
	: transform(t), width(w), height(h), trigger(isTrigger)
{ }

// basic AABB collision detection.
bool Collider::IsColliding(const Collider & other) const
{
	if (trigger || other.trigger)
	{
		// for now return true.
		return true;
	}
	return (transform.x < other.transform.x + other.width &&
		transform.x + width > other.transform.x && 
		transform.y < other.transform.y + other.height &&
		transform.y + height > other.transform.y);
}

void Collider::DrawCollider(Surface* screen)
{
	screen->Box(transform.x, transform.y, transform.x + width, transform.y + height, 0xff6969);
}