#pragma once
#include "EditorUI.h"
class Outliner :
    public EditorUI
{
private:
public:
    virtual void Tick_UI() override;
public:
    Outliner();
    virtual ~Outliner();
};

