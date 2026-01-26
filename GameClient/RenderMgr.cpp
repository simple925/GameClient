#include "pch.h"
#include "RenderMgr.h"
#include "Device.h"
RenderMgr::RenderMgr() {}
RenderMgr::~RenderMgr() {}
void RenderMgr::Init() {}
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
}

