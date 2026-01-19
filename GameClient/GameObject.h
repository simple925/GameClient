#pragma once
#include "Entity.h"
#include "Component.h"

class GameObject :
    public Entity
{
private:
    Ptr<Component> m_Com[(UINT)COMPONENT_TYPE::END];
public:
    void AddComponent(Ptr<Component> _Com);
public:
    GameObject();
    virtual ~GameObject();
};

