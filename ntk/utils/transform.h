#pragma once

/* Basically taken over from Unity to make things easier for myself */
class Transform
{
public:
	Transform(float startX = 0.0f, float startY = 0.0f) : x(startX), y(startY) { }

	void Translate(float deltaX, float deltaY);

	void SetPosition(float newX, float newY);
	std::pair<float, float> GetPosition() const;
public:
	// pos variables
	float x, y;
};