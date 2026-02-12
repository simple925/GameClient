#pragma once
#include "EditorUI.h"
class TransformUI :
    public EditorUI
{
private:
    Ptr<GameObject> m_TargetObject;
public:
    virtual void Tick_UI();
    void SetTargetObject(Ptr<GameObject> _TargetObject) { m_TargetObject = _TargetObject; }
public:
    TransformUI();
    virtual ~TransformUI();
};

