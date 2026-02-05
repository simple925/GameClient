#pragma once
#include "CScript.h"

class CMissileScript :
    public CScript
{
    Ptr<GameObject>     m_Target;
public:
    void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
public:
    virtual void Begin() override;
    virtual void Tick();
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
public:
    CMissileScript();
    virtual ~CMissileScript();
};

