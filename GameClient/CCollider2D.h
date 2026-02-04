#pragma once
#include "Component.h"
class CCollider2D :
    public Component
{
private:
    Vec2    m_Offset;
    Vec2    m_Scale;

    Matrix  m_matWorld;
public:
    GET_SET(Vec2, Offset);
    GET_SET(Vec2, Scale);
public:
    virtual void FinalTick() override;

public:
    CCollider2D();
    virtual ~CCollider2D();
};

