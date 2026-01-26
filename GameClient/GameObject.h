#pragma once
#include "Entity.h"
#include "components.h"

#define GET_COMPONENT(COM_NAME, COM_TYPE)     Ptr<C##COM_NAME> COM_NAME() { return (C##COM_NAME*)m_Com[(UINT)COMPONENT_TYPE::COM_TYPE].Get(); }

class GameObject :
    public Entity
{
private:
    Ptr<Component> m_Com[(UINT)COMPONENT_TYPE::END];
    vector<Ptr<CScript>>        m_vecScript;

    bool                        m_bIsHidden;
public:
    // 레벨이 처음 시작될때 호출되는 함수
    void Begin();

    // 매 프레임마다 할 일
    void Tick();

    // 매 프레임마다 Tick 이후에 뒷 수습작업 수행
    void FinalTick();

    // 자신을 타겟에 그림
    void Render();

    bool IsHidden() const { return m_bIsHidden; }
    void Hide() { m_bIsHidden = true; }
    void Show() { m_bIsHidden = false; }
public:
    void AddComponent(Ptr<Component> _Com);
    Ptr<Component> GetComponent(COMPONENT_TYPE _Type) { return m_Com[(UINT)_Type]; }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
public:
    GameObject();
    virtual ~GameObject();
};

