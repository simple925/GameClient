#include "pch.h"
#include "ALevel.h"
#include "CPlayerProjectile.h"
#include "AssetMgr.h"
#include "LevelMgr.h"

ALevel::ALevel()
	:Asset(ASSET_TYPE::LEVEL)
{}
ALevel::~ALevel() {};
void ALevel::Init()
{
	for (int i = 0; i < 30; ++i) {
		Ptr<GameObject> pBullet = new GameObject;
		pBullet->AddComponent(new CTransform);
		pBullet->AddComponent(new CMeshRender);
		pBullet->AddComponent(new CPlayerProjectile);
		//pBullet->Transform()->SetPos(vPos);
		pBullet->Transform()->SetScale(Vec3(0.2f, 0.2f, 1.f));
		pBullet->Hide();
		pBullet->MeshRender()->SetMesh(AssetMgr::GetInst()->FindAsset<AMesh>(L"q").Get());
		pBullet->MeshRender()->SetShader(AssetMgr::GetInst()->FindAsset<AGraphicShader>(L"shader3").Get());
		pBullet->MeshRender()->SetTexture(AssetMgr::GetInst()->FindAsset<ATexture>(L"m").Get());
		//pBullet->MeshRender()->SetTexture(AssetMgr::GetInst()->FindAsset<ATexture>(L"PlayerImage").Get());
		this->AddObject(1, pBullet);
	}
}
void ALevel::AddObject(int _LayerIdx, Ptr<GameObject> _Object)
{
	m_arrLayer[_LayerIdx].addObject(_Object);
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

void ALevel::Render()
{
	for (UINT i = 0; i < MAX_LAYER; ++i) {
		m_arrLayer[i].Render();
	}
}
