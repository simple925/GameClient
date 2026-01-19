#pragma once
#include "Component.h"
class CTransform :
    public Component
{
private:
    Vec3    m_Pos;
    Vec3    m_Scale;
    Vec3    m_Rotation;
public:
    // 할 일 수행
    void FinalTick();
    // 데이터를 GPU 메모리로 전송
    void Binding();
public:
    CTransform();
    virtual ~CTransform();
};

