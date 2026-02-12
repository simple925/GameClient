#pragma once
#include "EditorUI.h"
#include "TransformUI.h"
class Inspector
	: public EditorUI
{
private:
	Ptr<GameObject> m_TargetObject;
	Ptr<TransformUI> m_TransformUI;
public:
	void SetTargetObject(Ptr<GameObject> _Object);
public:
	virtual void Tick_UI()override;
public:
	Inspector();
	virtual ~Inspector();
};

