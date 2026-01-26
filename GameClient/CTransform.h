#pragma once
#include "Component.h"
class CTransform :
    public Component
{
private:
    Vec3    m_Pos;
    Vec3    m_Scale;
    Vec3    m_Rotation;

    // 단위벡터(길이가 1)
    Vec3    m_Dir[(UINT)DIR::END]; // 방향 벡터

    Matrix  m_matWorld;
public:
    // 세팅된 묶어주는 역할
    void FinalTick();
    // 데이터를 GPU 메모리로 전송
    void Binding();

    void SetPos(Vec3 _Pos){ m_Pos = _Pos ;}
    void SetScale(Vec3 _Scale) { m_Scale = _Scale;}
    void SetRotation(Vec3 _Rotation) { m_Rotation = _Rotation; }
    Vec3 GetPos(){ return m_Pos;}
    Vec3 GetScale() { return m_Scale;}
    Vec3 GetRotation() { return m_Rotation; }
    Vec3 GetDir(DIR _Type) { return m_Dir[(UINT)_Type]; }
public:
    CTransform();
    virtual ~CTransform();
};

