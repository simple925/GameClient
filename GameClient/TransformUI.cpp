#include "pch.h"
#include "TransformUI.h"
#include "GameObject.h"
TransformUI::TransformUI()
{
	SetUIName("TransformUI");
}

TransformUI::~TransformUI()
{
}

void TransformUI::Tick_UI()
{
	ImGui::Button("transform");
	if (nullptr == m_TargetObject) return;
	Vec3 vPos = m_TargetObject->Transform()->GetRelativePos();
	Vec3 vScale = m_TargetObject->Transform()->GetRelativeScale();
	Vec3 vRot = m_TargetObject->Transform()->GetRelativeRot();

	if (ImGui::DragFloat3("POSITION", vPos))
		m_TargetObject->Transform()->SetRelativePos(vPos);
	if (ImGui::DragFloat3("SCALE", vScale))
		m_TargetObject->Transform()->SetRelativeScale(vScale);

	Vec3 vDegree = vRot * 180 / XM_PI;
	if (ImGui::DragFloat3("ROTATION", vDegree))
	{
		vRot = vDegree * (XM_PI / 180.f);
		m_TargetObject->Transform()->SetRelativeRot(vRot);
	}
}