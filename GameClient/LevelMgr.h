#pragma once
#include "single.h"
#include "ALevel.h"

class LevelMgr
    : public singleton<LevelMgr>
{
    SINGLE(LevelMgr)
private:
    Ptr<ALevel>     m_CurLevel;
public:
    Ptr<ALevel>& GetLevel() { return m_CurLevel; }
    void Init();
    void Progress();


};

