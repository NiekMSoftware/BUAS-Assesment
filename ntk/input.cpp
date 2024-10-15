#include "precomp.h"
#include "input.h"

void Input::HandleInput(int key, bool isPressed)
{
	switch (key)
	{
	case GLFW_KEY_W: moveUp = isPressed; break;
	case GLFW_KEY_S: moveDown = isPressed; break;
	case GLFW_KEY_A: moveLeft = isPressed; break;
	case GLFW_KEY_D: moveRight = isPressed; break;
	}
}
