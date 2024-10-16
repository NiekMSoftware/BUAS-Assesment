#pragma once

/* Basically taken over from Unity to make things easier for myself */
class Transform
{
public:
	Transform() : position(0, 0) { }
	Transform(int startX, int startY) : position(startX, startY) { }
	Transform(int2& startPos) : position(startPos) { }

	void Translate(int deltaX, int deltaY);
	void Translate(int2& delta);

	void SetPosition(int newX, int newY);
	void SetPosition(int2& newPos);

public:
	int2 position;
};