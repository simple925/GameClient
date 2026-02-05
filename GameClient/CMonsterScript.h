#pragma once
#include "CScript.h"
class CMonsterScript :
    public CScript
{
private:
    Ptr<GameObject>     m_Target;
    float               accumulator;

public:
    void Tick() override;
    void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
    

public:
    CMonsterScript();
    virtual ~CMonsterScript();
};

