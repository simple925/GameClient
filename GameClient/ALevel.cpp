#include "pch.h"
#include "ALevel.h"
#include "AssetMgr.h"

ALevel::ALevel()
	:Asset(ASSET_TYPE::LEVEL)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i].m_LayerIdx = i;
	}
}
ALevel::~ALevel() {}
void ALevel::Begin()
{
	for (UINT i = 0; i < MAX_LAYER; ++i) {
		m_arrLayer[i].Begin();
	}
}
void ALevel::AddObject(int _LayerIdx, Ptr<GameObject> _Object)
{
	m_arrLayer[_LayerIdx].AddObject(_Object);
}

void ALevel::Deregister()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i].DeregisterObject();
	}
}

void ALevel::Tick()
{
	for (UINT i = 0; i < MAX_LAYER; ++i) {
		m_arrLayer[i].Tick();
	}
}

void ALevel::FinalTick()
{
	for (UINT i = 0; i < MAX_LAYER; ++i) {
		m_arrLayer[i].FinalTick();
	}
}
