#pragma once
#include "Component.h"

class CScript;
class CCollider2D;
typedef void(CScript::* COLLISION_EVENT)(CCollider2D*, CCollider2D*);
struct COLLISION_DELEGATE
{
    CScript* Inst; // 호출자
    COLLISION_EVENT MemFunc;
};

class CCollider2D :
    public Component
{
private:
    Vec2    m_Offset;
    Vec2    m_Scale;

    int     m_OverlapCount;
    Matrix  m_matWorld;

    vector<COLLISION_DELEGATE> m_vecBeginDel;
    vector<COLLISION_DELEGATE> m_vecOverDel;
    vector<COLLISION_DELEGATE> m_vecEndDel;
public:
    void AddDynamicBeginOverlap(CScript* _Inst, COLLISION_EVENT _MemFunc) { m_vecBeginDel.push_back(COLLISION_DELEGATE{_Inst, _MemFunc}); }
    void AddDynamicOverlap(CScript* _Inst, COLLISION_EVENT _MemFunc) { m_vecOverDel.push_back(COLLISION_DELEGATE{_Inst, _MemFunc}); }
    void AddDynamicEndOverlap(CScript* _Inst, COLLISION_EVENT _MemFunc) { m_vecEndDel.push_back(COLLISION_DELEGATE{_Inst, _MemFunc}); }

public:
    GET_SET(Vec2, Offset);
    GET_SET(Vec2, Scale);
private:
    void BeginOverlap(Ptr<CCollider2D> _Other);
    void Overlap(Ptr<CCollider2D> _Other);
    void EndOverlap(Ptr<CCollider2D> _Other);
    const Matrix& GetWorldMatrix() { return m_matWorld; }
public:
    virtual void FinalTick() override;
public:
    CCollider2D();
    virtual ~CCollider2D();

    friend class CollisionMgr;
};

