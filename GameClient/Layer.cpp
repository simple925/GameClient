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
		//if (m_vecObject[i]->IsHidden()) {
			//continue;
		//}
		m_vecObject[i]->Tick();
	}
}

void Layer::FinalTick()
{
	for (int i = 0; i < m_vecObject.size(); ++i) {
		m_vecObject[i]->FinalTick();
	}
}

void Layer::Render()
{
	for (int i = 0; i < m_vecObject.size(); ++i) {
		if (m_vecObject[i]->IsHidden()) continue;
		m_vecObject[i]->Render();
	}
}
