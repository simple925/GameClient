#pragma once
#include "CScript.h"
class CCamMoveScript
	: public CScript
{
private:
	Ptr<GameObject> m_Target;
public:
	void SetTarget(Ptr<GameObject> _Target) { m_Target = _Target; }
public:
	virtual void Tick() override;
private:
	void MovePerspective();
	void MoveOrthographic();
public:
	CCamMoveScript();
	~CCamMoveScript();
};

