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

	// 레이어 표현 과제
	//UINT        m_LayerCheck;   // 어떤 레이어만 화면에 렌더링 할 것인지 비트체크

	// 1. 카메라 객체를 미리 캐싱 (루프 밖에서 한 번만)
	Ptr<CCamera> pCamera = RenderMgr::GetInst()->GetPOVCamera();
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

	PROJ_TYPE ProjType = GetTarget()->Camera()->GetProjType();     // 투영 방식
	const char* items[] = { "ORTHOGRAPHIC","PERSPECTIVE"};
	//ImGui::Combo("combo", &item_current, items, 2); // 밑이랑 같은 뜻
	if (ImGui::Combo("combo", (int*)&ProjType, items, IM_COUNTOF(items)))
	{
		GetTarget()->Camera()->SetProjType(ProjType);
	}

	ImGui::BeginDisabled(ProjType == PROJ_TYPE::ORTHOGRAPHIC);
	ImGui::Text("FOV");
	ImGui::SameLine(100);
	float FOV = GetTarget()->Camera()->GetFOV();          // 원근투영 시야각
	if (ImGui::DragFloat("##FOV", &FOV, 0.1f))
	{ // 돌리효과 연출가능
		GetTarget()->Camera()->SetFOV(FOV);
	}
	ImGui::EndDisabled();



	
	
	float       m_Far;          // 카메라 시야 최대거리
	float       m_Width;        // 투영 가로길이
	float       m_AspectRatio;  // 종횡비(가로 / 세로), 세로대비 가로의 길이 비율
	float       m_OrthoScale;   // 직교투영 배율
	Matrix      m_matView;      // View 행렬;
	Matrix      m_matProj;      // Proj 행렬;
}
