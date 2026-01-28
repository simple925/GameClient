#include "pch.h"
#include "CMeshRender.h"

CMeshRender::CMeshRender()
	: Component(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}
void CMeshRender::FinalTick()
{
}
void CMeshRender::Render()
{
	// Mesh Shader 미등록 시
	if (nullptr == m_Mesh || nullptr == m_Material)
		return;
	m_Material->Binding();
	m_Mesh->Render();
}