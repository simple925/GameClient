#pragma once
#include "Asset.h"
#include "Layer.h"

class ALevel :
    public Asset
{
private:
    Layer       m_arrLayer[MAX_LAYER]; // 하나의 레벨에
public:
    void Begin();
    void Tick();
    void FinalTick();
public:
    void AddObject(int _LayerIdx, Ptr<GameObject> _Object);
    Layer* GetLayer(int _Idx) { assert(0 <= _Idx && _Idx < MAX_LAYER); return &m_arrLayer[_Idx]; }
    void Deregister();
public:
    ALevel();
    virtual ~ALevel();
};

