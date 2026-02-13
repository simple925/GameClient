#include "pch.h"
#include "CameraUI.h"
#include "RenderMgr.h"
#include "LevelMgr.h"

CameraUI::CameraUI()
	: ComponentUI(COMPONENT_TYPE::CAMERA, "CameraUI")
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Tick_UI()
{
	OutputTitle("Camera");

	Ptr<CCamera> pCamera = RenderMgr::GetInst()->GetPOVCamera();
	if (ImGui::TreeNode("Camera Matrices")) {
		Matrix matView = pCamera->GetViewMat();
		// 4x4 테이블로 행렬 값 출력 (InputFloat4 4개 사용)
		for (int r = 0; r < 4; ++r) {
			float row[4] = { matView.m[r][0], matView.m[r][1], matView.m[r][2], matView.m[r][3] };
			ImGui::PushID(r);
			ImGui::InputFloat4("##row", row, "%.2f", ImGuiInputTextFlags_ReadOnly);
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("LayerCheck"))
	{
		// 1. 카메라 객체를 미리 캐싱 (루프 밖에서 한 번만)
		Ptr<ALevel> pCurLevel = LevelMgr::GetInst()->GetLevel();
		if (nullptr == pCamera) {
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "No POV Camera Active");
			return;
		}

		// 현재 비트 상태를 한 번만 가져옴
		UINT layerCheck = pCamera->GetLayerCheck();

		// 2. 테이블 스타일 및 레이아웃 개선

		if (ImGui::BeginTable("LayerTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
		{
			for (int i = 0; i < 32; ++i)
			{
				ImGui::TableNextColumn();

				// 1. Level에서 해당 인덱스의 레이어 이름 가져오기
				string strName = "Empty";
				if (pCurLevel != nullptr)
				{
					Layer* pLayer = pCurLevel->GetLayer(i);
					if (pLayer != nullptr && !pLayer->GetName().empty())
					{
						strName.assign(pLayer->GetName().begin(), pLayer->GetName().end()); // 레이어에 설정된 이름
					}
				}

				// 2. 이름 구성 (예: [02] Player)
				char label[128];
				sprintf_s(label, "[%02d] %s", i, strName.c_str());

				// 3. 현재 상태 확인 및 체크박스 출력
				bool bIsOn = (layerCheck & (1 << i));

				// 체크박스 ID가 겹치지 않게 ##i 를 붙여주는 것이 좋습니다.
				if (ImGui::Checkbox(label, &bIsOn))
				{
					pCamera->LayerCheck(i); // 클릭 시 카메라 비트 토글
				}
			}
			ImGui::EndTable();
		}
		ImGui::TreePop();
	}

	ImGui::SeparatorText("##ProjType");

	PROJ_TYPE ProjType = GetTarget()->Camera()->GetProjType();     // 투영 방식
	const char* items[] = { "ORTHOGRAPHIC","PERSPECTIVE"};
	//ImGui::Combo("combo", &item_current, items, 2); // 밑이랑 같은 뜻
	ImGui::Text("ProjType");
	ImGui::SameLine(100);
	if (ImGui::Combo("##ProjType", (int*)&ProjType, items, IM_COUNTOF(items)))
	{
		GetTarget()->Camera()->SetProjType(ProjType);
	}

	// Near / Far Clip 제어 (공통)
	float fNear = pCamera->GetNear();
	float fFar = pCamera->GetFar();
	ImGui::Text("Near");
	ImGui::SameLine(100);
	if (ImGui::DragFloat("##Near", &fNear, 0.1f, 0.1f, fFar - 1.f)) pCamera->SetNear(fNear);
	ImGui::Text("Far");
	ImGui::SameLine(100);
	if (ImGui::DragFloat("##Far", &fFar, 1.0f, fNear + 1.f, 10000.0f)) pCamera->SetFar(fFar);

	ImGui::BeginDisabled(ProjType == PROJ_TYPE::ORTHOGRAPHIC);
	ImGui::Text("FOV");
	ImGui::SameLine(100);
	float FOV = GetTarget()->Camera()->GetFOV();          // 원근투영 시야각
	if (ImGui::DragFloat("##FOV", &FOV, 0.1f))
	{ // 돌리효과 연출가능
		GetTarget()->Camera()->SetFOV(FOV);
	}
	ImGui::EndDisabled();

	// Ortho Scale (직교 투영 전용)
	ImGui::BeginDisabled(ProjType == PROJ_TYPE::PERSPECTIVE);
	ImGui::Text("Ortho Scale");
	ImGui::SameLine(100);
	float fScale = pCamera->GetOrthoScale();
	if (ImGui::DragFloat("##OrthoScale", &fScale, 0.01f, 0.1f, 10.0f)) pCamera->SetOrthoScale(fScale);
	ImGui::EndDisabled();


	
	
	ImGui::SeparatorText("Camera Info");

	// 1. 읽기 전용 데이터 (Width, AspectRatio)
	float fWidth = pCamera->GetWidth();
	float fAspect = pCamera->GetAspectRatio();

	ImGui::Text("Viewport Width");
	ImGui::SameLine(120);
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f", fWidth);

	ImGui::Text("Aspect Ratio");
	ImGui::SameLine(120);
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f", fAspect);

	// 2. 카메라의 전방/상방/우측 벡터 (디버깅 시 매우 유용)
	if (ImGui::TreeNode("Camera Vectors"))
	{
		// View 행렬의 역행렬에서 방향 벡터를 추출하거나 
		// Transform 컴포넌트에서 직접 가져올 수 있습니다.
		Vec3 vForward = GetTarget()->Transform()->GetDir(DIR::FRONT);
		Vec3 vUp = GetTarget()->Transform()->GetDir(DIR::UP);
		Vec3 vRight = GetTarget()->Transform()->GetDir(DIR::RIGHT);

		ImGui::Text("Forward: "); ImGui::SameLine(); ImGui::Text("(%.2f, %.2f, %.2f)", vForward.x, vForward.y, vForward.z);
		ImGui::Text("Up:      "); ImGui::SameLine(); ImGui::Text("(%.2f, %.2f, %.2f)", vUp.x, vUp.y, vUp.z);
		ImGui::Text("Right:   "); ImGui::SameLine(); ImGui::Text("(%.2f, %.2f, %.2f)", vRight.x, vRight.y, vRight.z);

		ImGui::TreePop();
	}

	// 3. 편의 기능: 카메라 리셋 버튼
	if (ImGui::Button("Reset Camera Settings"))
	{
		pCamera->SetFOV(90.f); // 60도 정도의 기본값
		pCamera->SetFar(10000.f);
		pCamera->SetNear(1.f);
		pCamera->SetOrthoScale(1.f);
	}
}
