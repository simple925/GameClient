#include "pch.h"
#include "CMonsterScript.h"
#include "CMonsterProtile.h"
#include "GameObject.h"
#include "AssetMgr.h"
#include "TimeMgr.h"
CMonsterScript::CMonsterScript()
	: accumulator(0)
	, m_Target(nullptr)
{
}

CMonsterScript::~CMonsterScript()
{
}


void CMonsterScript::Tick()
{
	Vec3 vMyPos = Transform()->GetRelativePos();
	Vec3 vMyScale = Transform()->GetRelativeScale();
	Vec3 vRotation = Transform()->GetRelativeRot();
	vector<Vec3> directions = { 
		Vec3(1, 0, 0), // 오른쪽
		Vec3(-1, 0, 0), // 왼쪽
		Vec3(0, 1, 0), // 위
		Vec3(0, -1, 0), // 아래
		Vec3(0.707f, 0.707f, 0), // 오른쪽 위
		Vec3(-0.707f, 0.707f, 0), // 왼쪽 위
		Vec3(0.707f, -0.707f, 0), // 오른쪽 아래
		Vec3(-0.707f, -0.707f, 0) // 왼쪽 아래
	};
	accumulator += DT;

	if (accumulator > 1.f) {
		for (auto& dir : directions) {
			GameObject* pObject = new GameObject;
			pObject->SetName(L"EnermyMissile");
			pObject->AddComponent(new CTransform);
			pObject->AddComponent(new CMeshRender);
			pObject->AddComponent(new CCollider2D);

			Ptr<CMonsterProtile> pMissileScript = new CMonsterProtile;
			//pMissileScript->SetTarget(m_Target.Get());
			pMissileScript->SetTarget(GetOwner());
			pObject->AddComponent(pMissileScript.Get());

			pObject->Transform()->SetRelativePos(vMyPos + vMyScale * 10.f * dir);
			pObject->Transform()->SetRelativeScale(Vec3(10.f, 30.f, 1.f));
			pObject->Transform()->SetRelativeRot(vRotation);

			pObject->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"q"));
			pObject->MeshRender()->SetMtrl(AssetMgr::GetInst()->Find<AMaterial>(L"Std2DMtrl"));

			CreateObject(pObject, 6);
		}
		accumulator = 0.f;
	}

}