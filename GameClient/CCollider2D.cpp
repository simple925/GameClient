#include "pch.h"
#include "CCollider2D.h"

#include "RenderMgr.h"


CCollider2D::CCollider2D()
	: Component(COMPONENT_TYPE::COLLIDER2D)
	, m_Scale(Vec2(1.f, 1.f))
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::FinalTick()
{
	// XMMatrixTranslation 이동행렬
	Matrix matTran = XMMatrixTranslation(m_Offset.x, m_Offset.y, 0.f);
	// XMMatrixScaling 크기행렬
	Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, 0.f);

	m_matWorld = matScale * matTran;
	m_matWorld *= Transform()->GetWorldMat();

	DrawDebugRect(m_matWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
}
