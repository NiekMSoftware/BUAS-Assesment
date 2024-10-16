#include "precomp.h"
#include "transform.h"


void Transform::Translate(int deltaX, int deltaY)
{
	position.x += deltaX;
	position.y += deltaY;
}

void Transform::Translate(int2& delta)
{
	position += delta;
}

void Transform::SetPosition(int newX, int newY)
{
	position.x = newX;
	position.y = newY;
}

void Transform::SetPosition(int2& newPos)
{
	position = newPos;
}