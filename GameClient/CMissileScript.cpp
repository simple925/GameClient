#include "pch.h"
#include "CMissileScript.h"

#include "GameObject.h"
#include "TimeMgr.h"

CMissileScript::CMissileScript()
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::Tick()
{
	if (IsValid(m_Target))
	{
		Vec3 vTargetPos = m_Target->Transform()->GetWorldPos();
		Vec3 vPos = Transform()->GetRelativePos();
		//Vec3 vUp = Transform()->GetDir(DIR::UP);
		Vec3 vDirToTarget = vTargetPos - vPos;
		vDirToTarget.Normalize(); // 단위 벡터

		// 1. 회전값 계산 (atan2는 라디안 값을 반환함)
		// atan2(y, x) -> x축 기준으로 y만큼의 각도를 계산
		float fAngle = atan2f(vDirToTarget.y, vDirToTarget.x);

		// 2. Transform에 회전 적용 (Z축 회전)
		Vec3 vRot = Transform()->GetRelativeRot();
		vRot.z = fAngle;
		Transform()->SetRelativeRot(vRot);

		vPos += vDirToTarget * 300.f * DT;

		Transform()->SetRelativePos(vPos);
	}
}