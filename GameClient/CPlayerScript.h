#pragma once
#include "CScript.h"

enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	DASH,
};

struct DashInfo
{
	bool    bDashing = false;

	Vec3    vDir = Vec3(0.f, 0.f, 0.f);

	float   fDashTime = 0.f;
	float   fDashDuration = 0.2f;

	float   fDashSpeed = 1200.f;

	float   fCoolTime = 0.f;
	float   fCoolDuration = 1.f;

	float   fAfterImageAcc = 0.f;
	float   fAfterImageInterval = 0.03f;
};


class CPlayerScript :
	public CScript
{
private:
	Ptr<GameObject>     m_Target;
	Ptr<GameObject>		m_Light;
	int					m_iPrevDir;
	float				m_fLightAngle;

	/* 대시 관련 */
	DashInfo m_Dash;
	PLAYER_STATE m_State = PLAYER_STATE::IDLE;
private:
	void Move();
	void Shoot();
public:
	void Tick() override;
	bool IsMouseOver();
	void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
	void SetLight(Ptr<GameObject> _Light) { m_Light = _Light; }
public:
	CPlayerScript();
	~CPlayerScript();
};




