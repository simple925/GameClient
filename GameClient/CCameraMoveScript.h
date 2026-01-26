#pragma once
#include "CScript.h"
class CCamraMoveScript
	: public CScript
{
private:
public:
	virtual void Tick() override;
public:
	CCamraMoveScript();
	~CCamraMoveScript();
};

