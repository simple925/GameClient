#include "pch.h"
#include "Menu.h"

#include "EditorMgr.h"

void Menu::Tick()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Level Save", "Ctrl+S"))
			{
			}
			if (ImGui::MenuItem("Level Load", "Ctrl+L"))
			{
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			bool ShowDemo = EditorMgr::GetInst()->IsShowDemo();
			if (ImGui::MenuItem("Demo", nullptr, &ShowDemo, true))
			{
				EditorMgr::GetInst()->ShowDemo(ShowDemo);
			}

			Ptr<EditorUI> pInspector = EditorMgr::GetInst()->FindUI("Inspector");
			bool InspectorActive = pInspector->IsActive();
			if (ImGui::MenuItem("Inspector", nullptr, &InspectorActive))
			{
				pInspector->SetActive(InspectorActive);
			}

			Ptr<EditorUI> pOutliner = EditorMgr::GetInst()->FindUI("Outliner");
			bool OutlinerActive = pOutliner->IsActive();
			if (ImGui::MenuItem("Outliner", nullptr, &OutlinerActive))
			{
				pOutliner->SetActive(OutlinerActive);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void Menu::Tick_UI()
{
}

Menu::Menu()
	: EditorUI("Menu")
{
}

Menu::~Menu()
{
}
