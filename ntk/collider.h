#pragma once

class Collider
{
public:
	Collider(Transform t, float w, float h, bool isTrigger);

	bool IsColliding(const Collider& other) const;

	void DrawCollider(Surface* screen);
public:
	Transform transform;
	float width, height; // size of the collider
	bool trigger; // if true, acts as a trigger collider
};