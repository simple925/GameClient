#pragma once
#include "Entity.h"
#include "GameObject.h"
class Layer
	: public Entity
{
private:
	vector<Ptr<GameObject>> m_vecObject;
public:
	void Begin();
	void addObject(Ptr<GameObject> _Object) { m_vecObject.push_back(_Object); }
	void Tick();
	void FinalTick();
	vector<Ptr<GameObject>> GetVecObject() { return m_vecObject; }
	void Render();
public:
	Layer();
	~Layer();
};

