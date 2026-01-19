#include "pch.h"
#include "Device.h"
#include "PathMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "AMesh.h"
#include "AGraphicShader.h"

#include "GameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "ConstBuffer.h"
Ptr<AMesh>		g_RectMesh;
Ptr<AMesh>		g_TriMesh;
Ptr<AMesh>		g_QuadMesh;
// 그래픽 파이프라인 문서
//https://learn.microsoft.com/ko-kr/windows/uwp/graphics-concepts/graphics-pipeline


// 상수 버퍼
Ptr<ConstBuffer>		g_CB;

// 파이프라인
Ptr<AGraphicShader> g_Shader;
Ptr<AGraphicShader> g_Shader2;

// Contant Buffer(상수버퍼)
ComPtr<ID3D11Buffer>		g_CB;
Ptr<GameObject>				g_Object;
// 오브젝트 위치
Vec4 g_ObjectPos = Vec4(0.f, 0.f, 0.f, 0.f); 
// 오브젝트 크기
Vec4 g_ObjectScale = Vec4(1.f, 1.f, 1.f, 0.f);
// 오브젝트 회전값
Vec4 g_ObjectRot = Vec4(0.f, 0.f, 0.f, 0.f);




/*원
struct tTransform {
	Vec2 vOffset;   // 8byte 원의 중심 위치 (x, y)
	Vec2 vPadding;  // 8byte 16바이트 정렬을 위한 패딩
	Vec4 vColor;	// 16byte 추가
	float vZoom;
	float vDummy[3];// 12 (여기까지 48) -> 16의 배수 OK!
	Vec4 Rot;
};
//Vtx arrVtx[6] = {};
const int TRICOUNT = 100;
const int VTXCOUNT = TRICOUNT + 1; // 중심점 1개 + 외곽 점들
const int IDXCOUNT = TRICOUNT * 3;

struct Circle
{
	Vec2 vCenter;   // 중심 (NDC)
	float fRadius;
	Vec4 vColor;
	Vec4 fZoom;
	bool bSelected;
};
vector<Circle> g_vecCircle;
int g_iSelectedCircle = -1;
*/

int TestInit()
{
	/*
	AMesh* p = new AMesh;
	Ptr<AMesh> pMesh = p;
	p = pMesh.Get();
	p = new AMesh;
	//p->AddRef();
	Ptr<AMesh> pMesh2 = nullptr;
	*pMesh2.GetAdressOf() = p;

	pMesh == pMesh2;
	pMesh == p;
	p == pMesh;
	*/

	/*원
	const int TRICOUNT = 100;
	const int VTXCOUNT = TRICOUNT + 1;
	const int IDXCOUNT = TRICOUNT * 3;

	static Vtx arrVtx[VTXCOUNT];
	static UINT arrIdx[IDXCOUNT];
	// NDC 좌표계, 중심이 0,0, 위 아래 좌 우 로 +- 1 범위	
	// 1. 원점(0,0) 기준으로 정점 딱 한 번만 만들기
	float fRadius = 0.2f; // 원의 반지름

	// 0번 정점: 원의 중심
	arrVtx[0].vPos = Vec3(0.f, 0.f, 0.f); // 중심
	arrVtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f); // 하얀색
	arrVtx[0].vUV = Vec2(0.5f, 0.5f);

	// 외곽 정점들 계산
	for (int i = 0; i < TRICOUNT; ++i)
	{
		// 각도 계산 (360도를 삼각형 개수로 나눔)
		float fAngle = (XM_2PI / (float)TRICOUNT) * (float)i;

		// sin 앞에 '-'를 붙여서 시계 방향으로 정점을 생성합니다.
		arrVtx[i + 1].vPos = Vec3(cosf(fAngle) * fRadius, -sinf(fAngle) * fRadius, 0.f);
		arrVtx[i + 1].vColor = Vec4(1.f, 1.f, 1.f, 0.f);
		//arrVtx[i + 1].vUV = Vec2(0.f, 0.f);
	}
	// 인덱스 설정 (중심점 - 현재외곽 - 다음외곽)
	for (int i = 0; i < TRICOUNT; ++i)
	{
		arrIdx[i * 3 + 0] = 0;             // 항상 중심점
		arrIdx[i * 3 + 1] = i + 1;         // 현재 정점
		arrIdx[i * 3 + 2] = i + 2;         // 다음 정점

		// 마지막 삼각형은 다시 첫 번째 외곽 정점으로 연결
		if (i == TRICOUNT - 1)
			arrIdx[i * 3 + 2] = 1;
	}

	g_RectMesh = new AMesh;
	g_RectMesh->Create(arrVtx, sizeof(Vtx) * VTXCOUNT, arrIdx, sizeof(UINT) * IDXCOUNT);
	*/

	Vtx arrVtx[4] = {};

	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vUV = Vec2(0.f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 0.f, 1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vUV = Vec2(0.f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 1.f, 0.f, 0.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vUV = Vec2(0.f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 0.f);

	UINT arrIdx[6] = { 0, 2, 3, 0, 1, 2 };

	// 사각형 메쉬 생성
	g_QuadMesh = new AMesh;
	g_QuadMesh->Create(arrVtx, 4, arrIdx, 6);


	// 삼각형 메쉬
	Vtx arr[3] = {};
	arr[0].vPos = Vec3(0.f, 1.f, 0.f);
	arr[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arr[1].vPos = Vec3(1.f, -1.f, 0.f);
	arr[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arr[2].vPos = Vec3(-1.f, -1.f, 0.f);
	arr[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	UINT idx[3] = { 0 , 1 , 2 };

	g_TriMesh = new AMesh;
	g_TriMesh->Create(arr, 3, idx, 3);


	

	// VertexShader
	// 컴파일할 VertexShader 함수가 작성 되어있는 파일의 절대 경로

	// 파이프라인 생성
	g_Shader = new AGraphicShader;
	g_Shader->CreateVertexShader(L"Shader\\test.fx", "VS_Test");
	g_Shader->CreatePixelShader(L"Shader\\test.fx", "PS_Test");

	g_Shader2 = new AGraphicShader;
	g_Shader2->CreateVertexShader(L"Shader\\test.fx", "VS_Test2");
	g_Shader2->CreatePixelShader(L"Shader\\test.fx", "PS_Test2");


	/*원

	g_vecCircle.clear();

	for (int i = 0; i < 3; ++i)
	{
		Circle c = {};
		c.vCenter = Vec2(-0.5f + i * 0.5f, 0.f);
		c.fRadius = 0.2f;
		c.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		c.fZoom = Vec4(1.f, 1.f, 1.f, 0.f);
		c.bSelected = false;

		g_vecCircle.push_back(c);
	}
	*/

	g_Object = new GameObject;
	g_Object->AddComponent(new CTransform);
	g_Object->AddComponent(new CMeshRender);
	return S_OK;


}
/*원
int PickCircle(const Vec2& mouseNDC)
{
	for (int i = 0; i < g_vecCircle.size(); ++i)
	{
		Vec2 diff = mouseNDC - g_vecCircle[i].vCenter;
		float distSq = diff.LengthSquared();

		float r = g_vecCircle[i].fRadius * g_vecCircle[i].fZoom;

		if (distSq <= r * r)
			return i;
	}
	return -1;
}
Vec2 GetMouseNDC()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(Device::GetInst()->GetHwnd(), &pt);

	float width = Device::GetInst()->GetRenderResol().x;
	float height = Device::GetInst()->GetRenderResol().y;

	float x = (pt.x / width) * 2.f - 1.f;
	float y = 1.f - (pt.y / height) * 2.f;

	return Vec2(x, y);
}
*/

void TestTick()
{
	/*원
	static float fAccTime = 0.f;
	fAccTime += DT;
	float r = sinf(fAccTime * 1.5f) * 0.5f + 0.5f;
	float g = sinf(fAccTime * 2.1f) * 0.5f + 0.5f;
	float b = sinf(fAccTime * 0.7f) * 0.5f + 0.5f;
	//g_vTargetColor = Vec4(r, g, b, 1.f);
	if (KEY_TAP(KEY::LBUTTON))
	{
		Vec2 mouseNDC = GetMouseNDC();
		g_iSelectedCircle = PickCircle(mouseNDC);

		// 선택 상태 갱신
		for (int i = 0; i < g_vecCircle.size(); ++i)
			g_vecCircle[i].bSelected = (i == g_iSelectedCircle);
	}

	if (g_iSelectedCircle != -1)
	{
		Circle& c = g_vecCircle[g_iSelectedCircle];
		c.vColor = Vec4(r, g, b, 1.f);
		if (KEY_PRESSED(KEY::LEFT)) c.vCenter.x -= 1.f * DT;
		if (KEY_PRESSED(KEY::RIGHT)) c.vCenter.x += 1.f * DT;
		if (KEY_PRESSED(KEY::UP))    c.vCenter.y += 1.f * DT;
		if (KEY_PRESSED(KEY::DOWN))  c.vCenter.y -= 1.f * DT;

		if (KEY_PRESSED(KEY::W)) c.fZoom += 0.5f * DT;
		if (KEY_PRESSED(KEY::S)) c.fZoom -= 0.5f * DT;
		if (KEY_PRESSED(KEY::Z)) g_ObjectRot.z += DT * XM_PI;
	}
	*/
	if (KEY_PRESSED(KEY::RIGHT))
		g_ObjectPos.x += 0.5f * DT;
	if (KEY_PRESSED(KEY::LEFT))
		g_ObjectPos.x -= 0.5f * DT;
	if (KEY_PRESSED(KEY::UP))
		g_ObjectPos.y += 0.5f * DT;
	if (KEY_PRESSED(KEY::DOWN))
		g_ObjectPos.y -= 0.5f * DT;

	if (KEY_PRESSED(KEY::W))
	{
		g_ObjectScale.x += 0.5f * DT;
		g_ObjectScale.y += 0.5f * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		g_ObjectScale.x -= 0.5f * DT;
		g_ObjectScale.y -= 0.5f * DT;

		if (g_ObjectScale.x < 0.f)
			g_ObjectScale.x = 0.f;

		if (g_ObjectScale.y < 0.f)
			g_ObjectScale.y = 0.f;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		g_ObjectRot.z += DT * XM_PI;
	}
	// 회전
	// 삼각형 합,차 공식
	// 삼각함수(Sin, Cos, Tangent)
	// 방향벡터, 스칼라
	// 오브젝트 회전

	g_CB->SetData(&Trans);

	Transform Trans = {};
	Trans.Pos = g_ObjectPos;
	Trans.Scale = g_ObjectScale;
	Trans.Rot = g_ObjectRot;
	DEVICE::GetInst()->GetTransformBuffer()->;
	// 전역변수에 들어있는 오브젝트 위치 정보를 상수버퍼로 복사
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);
	memcpy(tMapSub.pData, &Trans, sizeof(Transform));
	CONTEXT->Unmap(g_CB.Get(), 0);
}



void TestRender()
{

	// 이전에 그려진 그림을 지운다.
	// 랜더타겟은
	Device::GetInst()->ClearTarget();
	

	// HLSL(High Level Shader Language) 5.0
	// Graphic Pipeline
	// 1. IA(Input Assembler)
	// 정점을 프로그래머가 설계하기 때문에, 전달 한 버텍스 버퍼안에서, 하나의 정점의 단위크기를 알려줘야 한다.
	

	g_CB->Binding();
	//CONTEXT->VSSetConstantBuffers(1/*상수버퍼를 바인딩할 레지스터 번호*/, 1, g_CB.GetAddressOf());

	g_Shader2->Binding();

	/*원
	for (Circle& c : g_vecCircle)
	{
		// 외곽선
		if (c.bSelected)
		{
			Transform outline = {};
			outline.Pos = c.vCenter;
			outline.Scale = c.fZoom * 1.08f;   // 살짝 크게
			outline.vColor = Vec4(1, 0, 0, 1);  // 빨간 테두리

			D3D11_MAPPED_SUBRESOURCE sub;
			CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
			memcpy(sub.pData, &outline, sizeof(outline));
			CONTEXT->Unmap(g_CB.Get(), 0);

			g_RectMesh->Render();
		}

		//  본체
		tTransform body = {};
		body.vOffset = c.vCenter;
		body.vZoom = c.fZoom;
		body.vColor = c.vColor;

		D3D11_MAPPED_SUBRESOURCE sub;
		CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, &body, sizeof(body));
		CONTEXT->Unmap(g_CB.Get(), 0);

		g_RectMesh->Render();
	}
	*/
	//g_RectMesh->Render();

	g_TriMesh->Render();
	g_QuadMesh->Render();
}

int TestFunc()
{
	static bool bInit = false;
	if (!bInit)
	{
		if (FAILED(TestInit()))
			return E_FAIL;

		bInit = true;
	}

	TestTick();

	TestRender();

	return S_OK;
}