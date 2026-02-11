#pragma once
#include "CScript.h"
class CPlayerScript :
	public CScript
{
private:
	Ptr<GameObject>     m_Target;
	Ptr<GameObject>		m_Light;
	int					m_iPrevDir;
	float				m_fLightAngle;
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

