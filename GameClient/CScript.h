#pragma once
#include "Component.h"
class CScript :
    public Component
{
private:

public:
    virtual void Tick() = 0;
    virtual void FinalTick() final {}; // final 오버라이딩 불가
protected:
    void Destroy();
public:
    CScript();
    virtual ~CScript();
};

