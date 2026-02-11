#include "pch.h"
#include "ALevel.h"
#include "AssetMgr.h"

ALevel::ALevel()
	:Asset(ASSET_TYPE::LEVEL)
	, m_Matrix{}
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

void ALevel::CheckCollisionLayer(UINT _LayerIdx1, UINT _LayerIdx2)
{
	UINT Row = _LayerIdx1;
	UINT Col = _LayerIdx2;

	// 더 작은 레이어 인덱스를 행으로 사용.
	if (_LayerIdx2 < _LayerIdx1)
	{
		Row = _LayerIdx2;
		Col = _LayerIdx1;
	}
	// 비트를 넣을땐 
	// 제거 &= -
	//

	m_Matrix[Row] ^= (1 << Col);
}

void ALevel::CheckCollisionLayer(const wstring& _LayerName1, UINT _LayerName2)
{
}

Ptr<GameObject> ALevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		const vector<Ptr<GameObject>>& vecParent =  m_arrLayer[i].GetParentObjects();
		for (const auto& gObj : vecParent) {
			list<Ptr<GameObject>> queue;
			queue.push_back(gObj);

			while (!queue.empty())
			{
				Ptr<GameObject> pObj = queue.front();
				queue.pop_front();

				// 찾음
				if (pObj->GetName() == _Name)
				{
					return pObj;
				}
				const vector<Ptr<GameObject>>& vecChild = pObj->GetChild();
				for (const auto& cgObj : vecChild)
				{
					queue.push_back(cgObj);
				}
			}
		}
	}
	// 없음
	return nullptr;
}