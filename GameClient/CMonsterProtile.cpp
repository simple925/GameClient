#include "pch.h"
#include "CMonsterProtile.h"

#include "GameObject.h"
#include "TimeMgr.h"

CMonsterProtile::CMonsterProtile()
	: m_Angle(0.f), m_Speed(200.f), m_RotateSpd(2.f)
{
}

CMonsterProtile::~CMonsterProtile()
{
}


void CMonsterProtile::Begin()
{
	Collider2D()->AddDynamicBeginOverlap(this, (COLLISION_EVENT)&CMonsterProtile::BeginOverlap);
	Collider2D()->AddDynamicOverlap(this, (COLLISION_EVENT)&CMonsterProtile::Overlap);
	Collider2D()->AddDynamicEndOverlap(this, (COLLISION_EVENT)&CMonsterProtile::EndOverlap);
}

void CMonsterProtile::Tick()
{
	if (IsValid(m_Target))
	{
		/*
		Vec3 vTargetPos = m_Target->Transform()->GetWorldPos();
		Vec3 vPos = Transform()->GetRelativePos();

		Vec3 vDirToTarget = vTargetPos - vPos;
		vDirToTarget.Normalize();
		vPos += vDirToTarget * 200.f * DT;

		Transform()->SetRelativePos(vPos);
		*/
		/*
		m_Angle += m_RotateSpd * DT;
		Vec3 vTargetPos = m_Target->Transform()->GetWorldPos();
		Vec3 vPos = Transform()->GetRelativePos();
		// 타겟 방향
		Vec3 vDirToTarget = vTargetPos - vPos;
		vDirToTarget.Normalize(); // 타겟 방향에 수직인 벡터 (XY 평면 기준)
		Vec3 vPerp(-vDirToTarget.y, vDirToTarget.x, 0.f); // 회전 각도에 따라 두 벡터를 섞음
		Vec3 vSpiralDir = vDirToTarget * cos(m_Angle) + vPerp * sin(m_Angle);
		vSpiralDir.Normalize(); // 이동
		vPos += vSpiralDir * m_Speed * DT;
		Transform()->SetRelativePos(vPos);
		*/
		// 각도 증가 (곡선 회전 속도)
		//m_Angle += m_RotateSpd * DT;
		/*
		Vec3 vTargetPos = m_Target->Transform()->GetWorldPos();
		Vec3 vPos = Transform()->GetRelativePos(); // 기본 타겟 방향
		Vec3 vDirToTarget = vTargetPos - vPos;
		vDirToTarget.Normalize();

		// 수직 벡터 (XY 평면 기준)
		Vec3 vPerp(-vDirToTarget.y, vDirToTarget.x, 0.f);

		// 곡선 강도 (값이 클수록 더 휘어짐)
		float curveStrength = 0.5f;

		Vec3 vCurveDir = vDirToTarget + vPerp * curveStrength; vCurveDir.Normalize();
		vCurveDir.Normalize();
		vPos += vCurveDir * m_Speed * DT;
		Transform()->SetRelativePos(vPos);
		*/
	}
	if (m_Owner->IsDead()) Destroy();
}

void CMonsterProtile::BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider)
{
	int OwnerLayerIdx = _OwnCollider->GetOwner()->GetLayerIdx();
	int OtherLayerIdx = _OtherCollider->GetOwner()->GetLayerIdx();
	if (OwnerLayerIdx == 6 && OtherLayerIdx == 5) Destroy();
}

void CMonsterProtile::Overlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider)
{
}

void CMonsterProtile::EndOverlap(CCollider2D* _OwnCollider, CCollider2D* _OtherCollider)
{
}

