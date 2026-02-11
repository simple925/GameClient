#include "pch.h"
#include "Inspector.h"
#include "LevelMgr.h"
#include "GameObject.h"
Inspector::Inspector()
{
	m_Target = LevelMgr::GetInst()->FindObjectByName(L"Player");
}

Inspector::~Inspector()
{
}

void Inspector::Tick_UI()
{
	if (nullptr == m_Target) return;
	Vec3 vPos = m_Target->Transform()->GetRelativePos();
	Vec3 vScale = m_Target->Transform()->GetRelativeScale();
	Vec3 vRot = m_Target->Transform()->GetRelativeRot();

	if (ImGui::DragFloat3("POSITION", vPos))
		m_Target->Transform()->SetRelativePos(vPos);
	if (ImGui::DragFloat3("SCALE", vScale))
		m_Target->Transform()->SetRelativeScale(vScale);
	
	Vec3 vDegree = vRot * 180 / XM_PI; // 라디안 값을 디그리로 변경
	if (ImGui::DragFloat3("ROTATION", vRot))
	{
		vRot = vDegree * (XM_PI / 180.f);
		m_Target->Transform()->SetRelativeRot(vRot);
	}
}