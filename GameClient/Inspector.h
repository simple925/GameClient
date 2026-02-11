#pragma once
#include "EditorUI.h"
#include <xkeycheck.h>
class Inspector
	: public EditorUI
{
private:
	Ptr<GameObject> m_Target;
public:
	virtual void Tick_UI()override;
public:
	Inspector();
	virtual ~Inspector();
};

