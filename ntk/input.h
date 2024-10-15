#pragma once

class Input
{
public:
	void HandleInput(int key, bool isPressed);

public:
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
};