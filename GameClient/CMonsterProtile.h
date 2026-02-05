#pragma once
#include "CScript.h"
class CMonsterProtile :
    public CScript
{
private: 
    float m_Angle; // 현재 각도 (라디안)
    float m_Speed; // 이동 속도
    float m_RotateSpd; // 회전 속도 (라디안/초)
    Ptr<GameObject>     m_Target;
    GameObject* m_Owner;
public:
    void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
    void SetOwner(GameObject* _Owner) { m_Owner = _Owner; }
public:
    virtual void Begin() override;
    virtual void Tick();
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
public:
    CMonsterProtile();
    virtual ~CMonsterProtile();
};

