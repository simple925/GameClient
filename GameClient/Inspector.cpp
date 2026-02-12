#include "pch.h"
#include "Inspector.h"
#include "LevelMgr.h"
#include "GameObject.h"

Inspector::Inspector()
{
	m_TransformUI = new TransformUI;
	AddChildUI(m_TransformUI.Get());

	SetTargetObject(LevelMgr::GetInst()->FindObjectByName(L"Player"));
}

Inspector::~Inspector()
{
}

void Inspector::SetTargetObject(Ptr<GameObject> _Object)
{
	m_TargetObject = _Object;
	m_TransformUI->SetTargetObject(m_TargetObject);
}

void Inspector::Tick_UI()
{
	if (nullptr == m_TargetObject) return;
	wstring Name = m_TargetObject->GetName();			// 2Byte
	string strName = string(Name.begin(), Name.end());	// 1Byte
	ImGui::Button(strName.c_str());
}

