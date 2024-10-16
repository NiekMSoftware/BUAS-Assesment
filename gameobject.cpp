#include "precomp.h"
#include "gameobject.h"

GameObject::GameObject(const char* fileName, const char* id, int numFrames)
: m_sprite(0, 0),
  m_transform(0, 0),
  m_collider(m_transform, 32, 32, false)
{
	ResourceHolder::GetInstance().LoadSprite(fileName, id, numFrames);
	m_sprite = *ResourceHolder::GetInstance().GetSprite(id);
}