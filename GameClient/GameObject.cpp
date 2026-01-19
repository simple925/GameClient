#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: m_Com{}
{
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Ptr<Component> _Com)
{
	// 해당 컴포넌트를 이미 가지고 있지 않아야 한다.
	assert(nullptr == m_Com[(UINT)_Com->GetType()]);
	_Com->m_Owner = this;
	m_Com[(UINT)_Com->GetType()] = _Com;
}