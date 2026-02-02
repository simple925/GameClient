#include "pch.h"
#include "Layer.h"
Layer::Layer()
{
}

Layer::~Layer()
{
}
void Layer::Begin()
{
	for (int i = 0; i < m_vecObject.size(); ++i) {
		m_vecObject[i]->Begin();
	}
}
void Layer::Tick()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i) {
		m_vecObject[i]->Tick();
	}
}

void Layer::FinalTick()
{
	vector<Ptr<GameObject>>::iterator iter = m_vecObject.begin();

	while (iter != m_vecObject.end()) {
		(*iter)->FinalTick();
		if ((*iter)->IsDead()) {
			iter = m_vecObject.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Layer::Render()
{
	for (int i = 0; i < m_vecObject.size(); ++i) {
		m_vecObject[i]->Render();
	}
}
