#pragma once
#include "EditorUI.h"
#include "ComponentUI.h"
class Inspector
	: public EditorUI
{
private:
	Ptr<GameObject> m_TargetObject;
	Ptr<ComponentUI> m_arrComUI[(UINT)COMPONENT_TYPE::END];

public:
	void SetTargetObject(Ptr<GameObject> _Object);
public:
	virtual void Tick_UI()override;
	void CreateChildUI();
public:
	Inspector();
	virtual ~Inspector();
};

