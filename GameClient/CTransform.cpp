#include "pch.h"
#include "CTransform.h"
#include "Device.h"
CTransform::CTransform()
	: Component(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
}

void CTransform::Binding()
{
	Transform Trans = {};
	Trans.Pos = m_Pos;
	Trans.Scale = m_Scale;
	Trans.Rot = m_Rotation;

	Device::GetInst()->GetConstBuffer();
}
