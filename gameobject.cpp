#include "precomp.h"
#include "gameobject.h"

GameObject::GameObject(const char* fileName, const char* id, int nf)
: m_transform(0, 0),
  m_collider(m_transform, 32, 32, false)
{
	ResourceHolder::GetInstance().LoadSprite(fileName, id, nf);
	m_sprite = ResourceHolder::GetInstance().GetSprite(id);
}

const Sprite& GameObject::getSprite()
{
	return *m_sprite;
}

const Transform& GameObject::getTransform()
{
	return m_transform;
}

const Collider& GameObject::getCollider()
{
	return m_collider;
}
