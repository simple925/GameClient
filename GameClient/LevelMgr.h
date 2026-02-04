#pragma once

#include "ALevel.h"

class LevelMgr
    : public singleton<LevelMgr>
{
    SINGLE(LevelMgr)
private:
    Ptr<ALevel>     m_CurLevel;

public:
    Ptr<ALevel> GetLevel() { return m_CurLevel; }

public: // 시점 함수 목록
    void Init();
    void Progress();
};

