#include "pch.h"
#include "Inspector.h"
#include "LevelMgr.h"
#include "GameObject.h"

#include "TransformUI.h"
#include "Collider2DUI.h"
#include "CameraUI.h"
#include "Light2DUI.h"
Inspector::Inspector()
	: EditorUI("Inspector")
{
	CreateChildUI();
	//SetTargetObject(LevelMgr::GetInst()->FindObjectByName(L"Player"));
	SetTargetObject(LevelMgr::GetInst()->FindObjectByName(L"Monster"));
}

Inspector::~Inspector()
{
}

void Inspector::SetTargetObject(Ptr<GameObject> _Object)
{
	m_TargetObject = _Object;
	for (const auto& com : m_arrComUI)
	{
		if (nullptr == com)
		{
			continue;
		}
		com->SetTarget(m_TargetObject);
	}
}

void Inspector::Tick_UI()
{
	if (nullptr == m_TargetObject) return;
	wstring Name = m_TargetObject->GetName();			// 2Byte
	string strName = string(Name.begin(), Name.end());	// 1Byte
	ImGui::Button(strName.c_str());
	ImGui::Separator();
}

