#pragma once
#include "CScript.h"
class CPlayerProjectile :
    public CScript
{
private:
    float m_fSpeed;
public:
    void Tick() override;
    CPlayerProjectile();
    ~CPlayerProjectile();
};

