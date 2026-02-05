#pragma once
#include "Asset.h"
#include "Layer.h"

class ALevel :
    public Asset
{
private:
    Layer       m_arrLayer[MAX_LAYER];  // 하나의 레벨에
    UINT        m_Matrix[MAX_LAYER];    // 레이어끼리 충돌검사를 진행할 마킹 데이터

public:
    void Begin();
    void Tick();
    void FinalTick();
    void CheckCollisionLayer(UINT _LayerIdx1, UINT _LayerIdx2);
    void CheckCollisionLayer(const wstring& _LayerName1, UINT _LayerName2);

    UINT* GetCllisionMatrix() { return m_Matrix; }
public:
    void AddObject(int _LayerIdx, Ptr<GameObject> _Object);
    Layer* GetLayer(int _Idx) { assert(0 <= _Idx && _Idx < MAX_LAYER); return &m_arrLayer[_Idx]; }
    void Deregister();
public:
    ALevel();
    virtual ~ALevel();
};

