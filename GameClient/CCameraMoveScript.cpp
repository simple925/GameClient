#include "pch.h"
#include "CCameraMoveScript.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "CTransform.h"
CCamraMoveScript::CCamraMoveScript()
{
}

CCamraMoveScript::~CCamraMoveScript()
{
}

void CCamraMoveScript::Tick()
{
	Vec3 vPos = Transform()->GetPos();

	if (KEY_PRESSED(KEY::W))
		vPos.y += DT * 0.5f;
	if (KEY_PRESSED(KEY::S))
		vPos.y -= DT * 0.5f;
	if (KEY_PRESSED(KEY::A))
		vPos.x -= DT * 0.5f;
	if (KEY_PRESSED(KEY::D))
		vPos.x += DT * 0.5f;

	Transform()->SetPos(vPos);
}