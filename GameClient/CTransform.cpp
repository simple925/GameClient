#include "pch.h"
#include "CTransform.h"
#include "Device.h"
CTransform::CTransform()
	: Component(COMPONENT_TYPE::TRANSFORM)
	, m_Scale(Vec3(1.f, 1.f, 1.f))
{
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
	

	// 행열의 4행은 이동정보를 갖도록 약속됨
	// 단위 행열 == 항등행열
	/*
		1 0 0 0
		0 1 0 0
		0 0 1 0
		0 0 0 1
	*/

	// 변환 적용 순서
	// 크(크기, 배율) -> 자(회전, 자전) -> 이(이동) -> 공(회전, 공전)
	// 크기 > 자전 > 이동 > 공전

	Matrix matScale = XMMatrixIdentity(); // 단위행열로 초기화
	matScale._11 = m_Scale.x;
	matScale._22 = m_Scale.y;
	matScale._33 = m_Scale.z;

	/*
	// z 회전
	float3x3 rotMat =
	{
		cos(g_ObjectRot.z), sin(g_ObjectRot.z), 0.f,
		-sin(g_ObjectRot.z), cos(g_ObjectRot.z), 0.f,
		0.f, 0.f, 1.f,
	};
	// y 회전
	float3x3 rotMat =
	{
		cos(g_ObjectRot.z), 0.f, sin(g_ObjectRot.z),
		0.f, 1.f, 0.f,
		-sin(g_ObjectRot.z), 0.f, cos(g_ObjectRot.z),
	};
	// x 회전
	float3x3 rotMat =
	{
		1.f, 0.f, 0.f,
		0.f, cos(g_ObjectRot.z), sin(g_ObjectRot.z),
		0.f, -sin(g_ObjectRot.z), cos(g_ObjectRot.z),
	};
	*/
	Matrix matRot = XMMatrixRotationX(m_Rotation.x) * XMMatrixRotationY(m_Rotation.y) * XMMatrixRotationZ(m_Rotation.z);

	Matrix matTrans = XMMatrixIdentity(); // 단위행열로 초기화
	matTrans._41 = m_Pos.x;
	matTrans._42 = m_Pos.y;
	matTrans._43 = m_Pos.z;

	m_matWorld = matScale * matRot * matTrans;
}

void CTransform::Binding()
{
	Transform Trans = {};
	//Trans.Pos = m_Pos;
	//Trans.Scale = m_Scale;
	//Trans.Rot = m_Rotation;
	Trans.matWorld = m_matWorld;

	// 전역변수에 들어있는 오브젝트 위치 정보를 상수버퍼로 복사
	Device::GetInst()->GetTransformBuffer()->SetData(&Trans);
	Device::GetInst()->GetTransformBuffer()->Binding();
}
