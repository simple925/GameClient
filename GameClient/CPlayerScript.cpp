#include "pch.h"
#include "CPlayerScript.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "RenderMgr.h"

#include "CTransform.h"
#include "GameObject.h"
#include "CMissileScript.h"

#include "AssetMgr.h"
#include "LevelMgr.h"
#include "TaskMgr.h"

bool CPlayerScript::IsMouseOver()
{
	// 1. 마우스 NDC 좌표 가져오기
	POINT pt;
	GetCursorPos(&pt);
	//ScreenToClient(, &pt);

	float width = (float)Device::GetInst()->GetRenderResol().x;
	float height = (float)Device::GetInst()->GetRenderResol().y;

	float x = (pt.x / width) * 2.f - 1.f;
	float y = 1.f - (pt.y / height) * 2.f;
	Vec2 mouseNDC = Vec2(x, y);

	// 2. 자신의 Transform 정보 가져오기
	Ptr<CTransform> trans = GetOwner()->Transform();
	Vec3 vPos = trans->GetRelativePos();
	Vec3 vScale = trans->GetRelativeScale();

	// 3. 충돌 판정 (AABB 기준)
	// 좀 더 정밀하게 하고 싶다면 여기서 m_pMesh 정보를 받아와 메쉬 타입별로 계산 가능
	if (mouseNDC.x >= vPos.x - vScale.x / 2.f && mouseNDC.x <= vPos.x + vScale.x / 2.f &&
		mouseNDC.y >= vPos.y - vScale.y / 2.f && mouseNDC.y <= vPos.y + vScale.y / 2.f)
	{
		return true;
	}

	return false;
}

CPlayerScript::CPlayerScript()
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Move()
{
	
	// down casting
	//Ptr<CTransform> pTrans;
	//if (COMPONENT_TYPE::TRANSFORM == m_Com[(UINT)COMPONENT_TYPE::TRANSFORM]->GetType()) {
		//pTrans = (CTransform*) m_Com[(UINT)COMPONENT_TYPE::TRANSFORM].Get();
	//}

	// 실패하면 return nullptr;
	// 상속 관계에서 부모 클래스에 가장함수가 1개라도 있으면, C++ 에서는 타입 정보를 자료형 별로 생성한다.
	// 이것을 기반으로 다운캐스팅 성공 여부를 판단할 수 있다.
	//pTrans = dynamic_cast<CTransform*>(m_Com[(UINT)COMPONENT_TYPE::TRANSFORM].Get());

	//CTransform* trans = pTrans.Get();
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vScale = Transform()->GetRelativeScale();
	Vec3 vRotation = Transform()->GetRelativeRot();

	Vec3 vUp = Transform()->GetDir(DIR::UP);
	Vec3 vDown = -vUp;

	if (KEY_PRESSED(KEY::UP))
		vPos += vUp * 400.5f * DT;
	if (KEY_PRESSED(KEY::DOWN))
		vPos += vDown * 400.5f * DT;

	if (KEY_PRESSED(KEY::RIGHT))
		vRotation.z -= XM_PI * DT;
	if (KEY_PRESSED(KEY::LEFT))
		vRotation.z += XM_PI * DT;

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeScale(vScale);
	Transform()->SetRelativeRot(vRotation);
}

void CPlayerScript::Shoot()
{
	if (KEY_TAP(KEY::SPACE))
	{
		// 미사일 역할의 오브젝트 생성
		GameObject* pObject = new GameObject;
		pObject->SetName(L"Missile");

		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		//pObject->AddComponent(new CMissileScript);

		Ptr<CMissileScript> pMissileScript = new CMissileScript;
		pMissileScript->SetTarget(m_Target.Get());
		pObject->AddComponent(pMissileScript.Get());

		Vec3 vMyPos = Transform()->GetRelativePos();
		Vec3 vMyScale = Transform()->GetRelativeScale();
		Vec3 vRotation = Transform()->GetRelativeRot();
		Vec3 vUp = Transform()->GetDir(DIR::UP);

		pObject->Transform()->SetRelativePos(vMyPos + vMyScale * 0.5f * vUp);
		pObject->Transform()->SetRelativeScale(Vec3(10.f, 30.f, 1.f));
		pObject->Transform()->SetRelativeRot(vRotation);

		pObject->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"q"));
		pObject->MeshRender()->SetMtrl(AssetMgr::GetInst()->Find<AMaterial>(L"Std2DMtrl"));

		CreateObject(pObject, 2);
	}
	if (KEY_TAP(KEY::Z)) {
		DrawDebugCircle(Transform()->GetRelativePos(), 100.f, Vec4(1.f, 0.f, 0.f, 1.f), 2.f);
	}

	if (KEY_TAP(KEY::X)) {
		Destroy();
	}
	
}

void CPlayerScript::Tick()
{
	Move();

	Shoot();
	if (KEY_PRESSED(KEY::X))
	{
		MeshRender()->GetMtrl()->SetScalar(INT_0, 1);
	}
	else
	{
		MeshRender()->GetMtrl()->SetScalar(INT_0, 0);
	}

	Ptr<GameObject> pChild = GetOwner()->GetChild(0);

	Vec3 vRelativePos = pChild->Transform()->GetRelativePos();
	Vec3 vWorldPos = pChild->Transform()->GetWorldPos();
}
