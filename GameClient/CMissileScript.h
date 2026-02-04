#pragma once
#include "CScript.h"

class CMissileScript :
    public CScript
{
    Ptr<GameObject>     m_Target;

public:
    void Tick();
    void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
public:
    CMissileScript();
    virtual ~CMissileScript();
};

