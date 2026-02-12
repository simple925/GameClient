#include "pch.h"
#include "Collider2DUI.h"


Collider2DUI::Collider2DUI()
	: ComponentUI(COMPONENT_TYPE::COLLIDER2D, "Collider2D")
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::Tick_UI()
{
	OutputTitle("Collider2D");

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Offset");
	ImGui::SameLine(100);
	Vec2 Offset = GetTarget()->Collider2D()->GetOffset();
	if (ImGui::DragFloat2("##Offset", Offset, 0.01f))
	{
		GetTarget()->Transform()->Collider2D()->SetOffset(Offset);
	}

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Scale");
	ImGui::SameLine(100);
	Vec2 Scale = GetTarget()->Collider2D()->GetScale();
	if (ImGui::DragFloat2("##Scale", Scale, 0.01f))
	{
		GetTarget()->Transform()->Collider2D()->SetScale(Scale);
	}


}