#pragma once
#include "Component.h"
class CScript :
    public Component
{
private:

public:
    virtual void Tick() = 0;
    virtual void FinalTick() final {}; // final 오버라이딩 불가
public:
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) {}
    virtual void Overlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider) {}
protected:
    void Destroy();
public:
    CScript();
    virtual ~CScript();
};

