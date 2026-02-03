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

		Vec3 vDirToTarget = vTargetPos - vPos;
		vDirToTarget.Normalize();

		vPos += vDirToTarget * 200.f * DT;

		Transform()->SetRelativePos(vPos);
	}
}