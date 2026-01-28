#include "pch.h"
#include "AMaterial.h"


AMaterial::AMaterial()
	: Asset(ASSET_TYPE::MATERIAL)
{
}

AMaterial::~AMaterial()
{
}


void AMaterial::Binding()
{
	m_Shader->Binding();
	for (int i = 0; i < TEX_END; ++i)
	{
		if (nullptr == m_Tex[i]) continue;
		m_Tex[i]->Binding(i);
	}
}