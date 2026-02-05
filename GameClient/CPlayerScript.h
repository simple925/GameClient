#pragma once
#include "CScript.h"
class CPlayerScript :
	public CScript
{
private:
	Ptr<GameObject>     m_Target;
	int					m_iPrevDir;
private:
	void Move();
	void Shoot();
public:
	void Tick() override;
	bool IsMouseOver();
	void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
public:
	CPlayerScript();
	~CPlayerScript();
};

