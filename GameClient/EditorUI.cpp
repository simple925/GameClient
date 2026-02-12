#include "pch.h"
#include "EditorUI.h"
#include "ImGui/imgui.h"
EditorUI::EditorUI(const string& _Name)
	: m_UIName(_Name)
	, m_Active(true)
	, m_Parent(nullptr)
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Tick()
{
	if (nullptr == m_Parent)
	{
		ImGui::Begin(GetUIName().c_str(), &m_Active);

		Tick_UI();
		for (const auto& child : m_ChildUI)
		{
			if (child->IsActive()) {
				child->Tick();
				ImGui::Separator();
			}
		}

		ImGui::End();
	}
	else
	{
		ImGui::BeginChild(GetUIName().c_str(), m_SizeAsChild);

		Tick_UI();
		for (const auto& child : m_ChildUI)
		{
			if (child->IsActive()) {
				child->Tick();
				ImGui::Separator();
			}
		}

		ImGui::EndChild();
	}
}

Vec2::operator ImVec2() const
{
	return ImVec2(x, y);
}

Vec4::operator ImVec4() const
{
	return ImVec4(x, y, z, w);
}