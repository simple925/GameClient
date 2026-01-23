#include "pch.h"
#include "CPlayerProjectile.h"
#include "CTransform.h"

#include "TimeMgr.h"

#include "GameObject.h"

void CPlayerProjectile::Tick()
{
	// ÀÌµ¿
	Vec3 vPos = GetOwner()->Transform()->GetPos();
	vPos.y += m_fSpeed * DT;
	GetOwner()->Transform()->SetPos(vPos);


	// Ç®¿¡ ¹Ý³³
	if (vPos.y > 20.f) {
		// À§Ä¡¸¦ ÃÊ±âÈ­ÇÏ°í ¼û±è
		GetOwner()->Transform()->SetPos(Vec3(0.f, 0.f, 0.f));
		GetOwner()->Hide();
	}
}

CPlayerProjectile::CPlayerProjectile()
	: m_fSpeed(5.f)
{
}

CPlayerProjectile::~CPlayerProjectile()
{
}
