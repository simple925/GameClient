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
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetSizeAsChild(Vec2(0.f, 210.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM].Get());


	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetSizeAsChild(Vec2(0.f, 200.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D].Get());

	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetSizeAsChild(Vec2(0.f, 200.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA].Get());

	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetSizeAsChild(Vec2(0.f, 200.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D].Get());

	SetTargetObject(LevelMgr::GetInst()->FindObjectByName(L"MainCamera"));
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

