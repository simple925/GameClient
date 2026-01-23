#pragma once
#include "CScript.h"
class CPlayerScript :
    public CScript
{
private:
    bool m_bSelected;
private:
    void Move();
    void Shoot();
public:
    void Tick() override;
    bool IsMouseOver();
public:
    CPlayerScript();
    ~CPlayerScript();
};

