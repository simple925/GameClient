#include "pch.h"
#include "RenderMgr.h"
#include "Device.h"
#include "AssetMgr.h"
#include "TimeMgr.h"

RenderMgr::RenderMgr() {}
RenderMgr::~RenderMgr() {}

void RenderMgr::Init()
{
	m_DbgObj = new GameObject;
	m_DbgObj->AddComponent(new CTransform);
	m_DbgObj->AddComponent(new CMeshRender);



	m_DbgObj->MeshRender()->SetMtrl(FIND(AMaterial, L"DbgMtrl"));
}
void RenderMgr::Progress()
{
	//
	Device::GetInst()->ClearTarget();
	//m_CurLevel->Render();
	if (nullptr == m_MainCam) {
		return;
	}
	// 카메라를 이용해서 그림
	m_MainCam->Render();

	// 디버그 렌더링 요청 처리
	Render_Debug();
}

void RenderMgr::Render_Debug()
{
	list<DbgInfo>::iterator iter = m_DbgInfoList.begin();
	while (iter != m_DbgInfoList.end())
	{
		switch ((*iter).Shape)
		{
		case DBG_SHAPE::RECT:
			m_DbgObj->MeshRender()->SetMesh(FIND(AMesh, L"q_debug"));
			break;
		case DBG_SHAPE::CIRCLE:
			m_DbgObj->MeshRender()->SetMesh(FIND(AMesh, L"CircleMesh_LineStrip"));
			break;
		case DBG_SHAPE::CUBE:
			m_DbgObj->MeshRender()->SetMesh(FIND(AMesh, L"cube"));
			break;
		case DBG_SHAPE::SPHERE:
			m_DbgObj->MeshRender()->SetMesh(FIND(AMesh, L"sphere"));
			break;
		}
		// Transform 설정
		m_DbgObj->Transform()->SetRelativePos((*iter).Pos);
		m_DbgObj->Transform()->SetRelativeScale((*iter).Scale);
		m_DbgObj->Transform()->SetRelativeRot((*iter).Rotation);
		m_DbgObj->FinalTick();

		// Material 설정
		m_DbgObj->MeshRender()->GetMtrl()->SetScalar(VEC4_0, (*iter).Color);

		// Render 요청
		m_DbgObj->Render();

		// 렌더링 시간 누적
		(*iter).Age += DT;

		// 최대 수명에 도달하면 정보 삭제
		if ((*iter).Life < (*iter).Age)
		{
			// 다음 이터레이터를 줌 삭제하면 그래서 반복문 안에서 iter 를 삭제하면 else 로 구분해서 증가 시켜야함
			iter = m_DbgInfoList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}