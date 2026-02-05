#include "pch.h"
#include "CCollider2D.h"

#include "RenderMgr.h"


CCollider2D::CCollider2D()
	: Component(COMPONENT_TYPE::COLLIDER2D)
	, m_Scale(Vec2(1.f, 1.f))
	, m_OverlapCount(0)
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

	if (0 < m_OverlapCount)
		DrawDebugRect(m_matWorld, Vec4(1.f, 0.f, 0.f, 1.f), 0.f);
	else if (0 == m_OverlapCount)
		DrawDebugRect(m_matWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
	else
		assert(nullptr);
}

void CCollider2D::BeginOverlap(Ptr<CCollider2D> _Other)
{
	for (size_t i = 0; i < m_vecBeginDel.size(); ++i)
	{
		(m_vecBeginDel[i].Inst->*m_vecBeginDel[i].MemFunc)(this, _Other.Get());
	}
	++m_OverlapCount;
}

void CCollider2D::Overlap(Ptr<CCollider2D> _Other)
{ // 프레임단위 연산이 필요
	for (size_t i = 0; i < m_vecOverDel.size(); ++i)
	{
		(m_vecOverDel[i].Inst->*m_vecOverDel[i].MemFunc)(this, _Other.Get());
	}
}

void CCollider2D::EndOverlap(Ptr<CCollider2D> _Other)
{
	for (size_t i = 0; i < m_vecEndDel.size(); ++i)
	{
		(m_vecEndDel[i].Inst->*m_vecEndDel[i].MemFunc)(this, _Other.Get());
	}
	--m_OverlapCount;
}
