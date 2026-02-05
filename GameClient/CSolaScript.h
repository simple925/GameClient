#pragma once
#include "CScript.h"
class CSolaScript :
    public CScript
{
private:
public:
    void Tick() override;
public:
    CSolaScript();
    ~CSolaScript();
};

