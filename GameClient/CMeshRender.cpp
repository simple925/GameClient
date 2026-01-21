#include "pch.h"
#include "CMeshRender.h"

CMeshRender::CMeshRender()
	: Component(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}
void CMeshRender::Render()
{
	if (nullptr != m_Tex) {
		// t0에 바인딩
		m_Tex->Binding(0);
	}
	m_Shader->Binding();

	m_Mesh->Render();
}