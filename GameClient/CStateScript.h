#pragma once
#include "CScript.h"
class CStateScript :
    public CScript
{
private:
    int m_iHP;
    int m_iMaxHP;
public:
    // 공통 로직: 데미지 입기
    void TakeDamage(int _Damage);
    // Getter / Setter
    GET_SET(int, iHP);
    
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) override;
public:
    CStateScript();
    virtual ~CStateScript();
};

