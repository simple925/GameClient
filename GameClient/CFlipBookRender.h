#pragma once
#include "CRenderComponent.h"
#include "AFlipbook.h"
class CFlipBookRender :
    public CRenderComponent
{
private:
    Ptr<AFlipbook>        m_Flipbook;

public:
    void SetFlipbook(Ptr<AFlipbook> _Flipbook) { m_Flipbook = _Flipbook; }

public:
    virtual void FinalTick() override;
    virtual void Render() override;
    virtual void CreateMaterial() override;
public:
    CFlipBookRender();
    virtual ~CFlipBookRender();
};

