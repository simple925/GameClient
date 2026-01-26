#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "RenderMgr.h"
//int TestFunc();

Engine::Engine()
	: m_hInst(nullptr)
	, m_hWnd(nullptr)
	, m_Resolution{}
{
}

Engine::~Engine()
{}

int Engine::Progress()
{
	TimeMgr::GetInst()->Tick();
	KeyMgr::GetInst()->Tick();

	// LevelMgr 업데이트
	LevelMgr::GetInst()->Progress();

	// RenderMgr 렌더링
	RenderMgr::GetInst()->Progress();

	// 랜더타겟에 그려진 그림을, 윈도우 비트맵으로 복사
	Device::GetInst()->Present();
	return S_OK;
}

