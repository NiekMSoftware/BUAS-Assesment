#include "precomp.h"
#include "transform.h"

void Transform::Translate(float deltaX, float deltaY)
{
	x += deltaX;
	y += deltaY;
}

void Transform::SetPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}

std::pair<float, float> Transform::GetPosition() const
{
	return std::make_pair(x, y);
}