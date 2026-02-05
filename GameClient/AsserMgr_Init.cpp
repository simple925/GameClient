#include "pch.h"
#include "AssetMgr.h"

void AssetMgr::Init()
{
	CreateEngineMesh();
	CreateEngineShader();
	CreateEngineTexture();
	CreateEngineMaterial();
	CreateEngineSprite();
}

void AssetMgr::CreateEngineMesh()
{
	Ptr<AMesh> pMesh = nullptr;
	// 네모
	Vtx arrVtx[4] = {};
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 0.f, 1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);
	arrVtx[2].vColor = Vec4(0.f, 1.f, 0.f, 0.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 0.f);
	UINT arrIdx[6] = { 0, 2, 3, 0, 1, 2 };
	// 사각형 메쉬 생성
	pMesh = new AMesh;
	pMesh->SetName(L"1_네모");
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"q", pMesh.Get());


	arrIdx[0] = 0;
	arrIdx[1] = 1;
	arrIdx[2] = 2;
	arrIdx[3] = 3;
	arrIdx[4] = 0;
	pMesh = new AMesh;
	pMesh->SetName(L"2_네모_debug");
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	AddAsset(L"q_debug", pMesh.Get());

	// 동구람위
	const int TRICOUNT = 40;
	const int VTXCOUNT = TRICOUNT + 1;
	const int IDXCOUNT = TRICOUNT * 3;
	Vtx oVtx[VTXCOUNT] = {};
	UINT oIdx[IDXCOUNT] = {};

	float fRadius = 0.5f; // Scale로 조절할 것이므로 기본 크기는 1로 설정
	oVtx[0].vPos = Vec3(0.f, 0.f, 0.f);
	oVtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	for (int i = 0; i < TRICOUNT; ++i) {
		float fAngle = (XM_2PI / (float)TRICOUNT) * (float)i;
		oVtx[i + 1].vPos = Vec3(cosf(fAngle) * fRadius, -sinf(fAngle) * fRadius, 0.f);
		oVtx[i + 1].vColor = Vec4(
			(float)rand() / (float)RAND_MAX,
			(float)rand() / (float)RAND_MAX,
			(float)rand() / (float)RAND_MAX,
			1.f
		);
	}
	for (int i = 0; i < TRICOUNT; ++i) {
		oIdx[i * 3 + 0] = 0;
		oIdx[i * 3 + 1] = i + 1;
		oIdx[i * 3 + 2] = (i == TRICOUNT - 1) ? 1 : i + 2;
	}
	pMesh = new AMesh;
	pMesh->SetName(L"3_동구람위");
	pMesh->Create(oVtx, VTXCOUNT, oIdx, IDXCOUNT);
	AddAsset(L"c", pMesh.Get());

	// 셈오
	Vtx arr[3] = {};
	arr[0].vPos = Vec3(0.f, 1.f, 0.f);
	arr[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arr[0].vUV = Vec2(0.5f, 0.0f);

	arr[1].vPos = Vec3(1.f, -1.f, 0.f);
	arr[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arr[1].vUV = Vec2(1.0f, 1.0f);

	arr[2].vPos = Vec3(-1.f, -1.f, 0.f);
	arr[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arr[2].vUV = Vec2(0.0f, 1.0f);

	UINT idx[3] = { 0 , 1 , 2 };

	pMesh = new AMesh;
	pMesh->Create(arr, 3, idx, 3);
	pMesh->SetName(L"4_셈오1");
	AddAsset(L"t", pMesh.Get());

	// ===================
	// Cube (3D 정육면체)
	// ===================
	Vtx cubeVtx[8] = {};

	// 앞면 (Z = -0.5f)
	cubeVtx[0].vPos = Vec3(-0.5f, 0.5f, -0.5f); cubeVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f); cubeVtx[0].vUV = Vec2(0.f, 0.f);
	cubeVtx[1].vPos = Vec3(0.5f, 0.5f, -0.5f); cubeVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f); cubeVtx[1].vUV = Vec2(1.f, 0.f);
	cubeVtx[2].vPos = Vec3(0.5f, -0.5f, -0.5f); cubeVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f); cubeVtx[2].vUV = Vec2(1.f, 1.f);
	cubeVtx[3].vPos = Vec3(-0.5f, -0.5f, -0.5f); cubeVtx[3].vColor = Vec4(1.f, 1.f, 1.f, 1.f); cubeVtx[3].vUV = Vec2(0.f, 1.f);

	// 뒷면 (Z = 0.5f)
	cubeVtx[4].vPos = Vec3(-0.5f, 0.5f, 0.5f); cubeVtx[4].vColor = Vec4(1.f, 0.f, 1.f, 1.f); cubeVtx[4].vUV = Vec2(0.f, 0.f);
	cubeVtx[5].vPos = Vec3(0.5f, 0.5f, 0.5f); cubeVtx[5].vColor = Vec4(1.f, 1.f, 0.f, 1.f); cubeVtx[5].vUV = Vec2(1.f, 0.f);
	cubeVtx[6].vPos = Vec3(0.5f, -0.5f, 0.5f); cubeVtx[6].vColor = Vec4(0.f, 1.f, 1.f, 1.f); cubeVtx[6].vUV = Vec2(1.f, 1.f);
	cubeVtx[7].vPos = Vec3(-0.5f, -0.5f, 0.5f); cubeVtx[7].vColor = Vec4(0.f, 0.f, 0.f, 1.f); cubeVtx[7].vUV = Vec2(0.f, 1.f);

	// 인덱스 (삼각형 12개, 시계 방향)
	UINT cubeIdx[36] = {
		0, 1, 2, 0, 2, 3, // 앞
		4, 6, 5, 4, 7, 6, // 뒤
		4, 5, 1, 4, 1, 0, // 위
		3, 2, 6, 3, 6, 7, // 아래
		4, 0, 3, 4, 3, 7, // 왼쪽
		1, 5, 6, 1, 6, 2  // 오른쪽
	};

	pMesh = new AMesh;
	pMesh->SetName(L"5_큐브");
	pMesh->Create(cubeVtx, 8, cubeIdx, 36);
	AddAsset(L"CubeMesh", pMesh.Get());

	// 원
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	Vtx v;
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.5f, 0.5f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	float Theta = 0.f;
	float Radius = 0.5f;
	float Slice = 40.f;

	// 원의 테두리 정점 추가
	for (int i = 0; i < (int)Slice + 1; ++i)
	{
		v.vPos = Vec3(Radius * cosf(Theta), Radius * sinf(Theta), 0.f);
		//v.vUV = Vec2(0.5f, 0.5f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);

		// XM_2PI 360도
		Theta += XM_2PI / Slice;
	}

	// 인덱스
	for (int i = 0; i < (int)Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new AMesh;
	pMesh->SetName(L"6_원");
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh", pMesh.Get());

	vecIdx.clear();
	for (int i = 0; i < (int)Slice + 1; ++i) {
		vecIdx.push_back(i + 1);
	}

	pMesh = new AMesh;
	pMesh->SetName(L"7_원_debug");
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh_LineStrip", pMesh.Get());
}

void AssetMgr::CreateEngineShader()
{
	Ptr<AGraphicShader> pShader = nullptr;

	pShader = new AGraphicShader;
	pShader->CreateVertexShader(L"Shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"Shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	AddAsset(L"Std2DShader", pShader.Get());

	pShader = new AGraphicShader;
	pShader->CreateVertexShader(L"Shader\\dbg.fx", "VS_Debug");
	pShader->CreatePixelShader(L"Shader\\dbg.fx", "PS_Debug");
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	AddAsset(L"DbgShader", pShader.Get());
}

void AssetMgr::CreateEngineTexture()
{
	Ptr<ATexture> pTex = nullptr;
	wstring FilePath = CONTENT_PATH;

	pTex = new ATexture;
	FilePath += L"Texture\\Character.png";
	pTex->Load(FilePath);
	AddAsset(L"PlayerImage", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\Fighter.bmp";
	pTex->Load(FilePath);
	AddAsset(L"Fighter", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\1945\\back1.png";
	pTex->Load(FilePath);
	AddAsset(L"back_1", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\1945\\p.png";
	pTex->Load(FilePath);
	AddAsset(L"p", pTex.Get());
	pTex = nullptr;
	pTex = new ATexture;
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\1945\\m.bmp";
	pTex->Load(FilePath);
	AddAsset(L"m", pTex.Get());

	/*
	pTex = nullptr;
	pTex = new ATexture;
	pTex->SetName(L"태양");
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\sola.png";
	pTex->Load(FilePath);
	AddAsset(L"sola", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	pTex->SetName(L"지구");
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\earth.png";
	pTex->Load(FilePath);
	AddAsset(L"earth", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	pTex->SetName(L"수성");
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\mercury.png";
	pTex->Load(FilePath);
	AddAsset(L"mercury", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	pTex->SetName(L"금성");
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\venus.png";
	pTex->Load(FilePath);
	AddAsset(L"venus", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	pTex->SetName(L"우주");
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\univers.jpeg";
	pTex->Load(FilePath);
	AddAsset(L"univers", pTex.Get());

	pTex = nullptr;
	pTex = new ATexture;
	pTex->SetName(L"슬라임");
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\slime_run.png";
	pTex->Load(FilePath);
	AddAsset(L"slime", pTex.Get());
	*/
	pTex = new ATexture;
	FilePath = CONTENT_PATH;
	FilePath += L"Texture\\link.png";
	pTex->Load(FilePath);
	AddAsset(L"Link", pTex.Get());
}

void AssetMgr::CreateEngineMaterial()
{
	// 재질 만들기
	Ptr<AMaterial> pMtrl = nullptr;

	pMtrl = new AMaterial;
	pMtrl->SetName(L"Std2DMtrl");
	pMtrl->SetShader(Find<AGraphicShader>(L"Std2DShader"));
	pMtrl->SetTexture(TEX_0, Find<ATexture>(L"Fighter"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());

	pMtrl = new AMaterial;
	pMtrl->SetName(L"m_sola");
	pMtrl->SetTexture(TEX_0, Find<ATexture>(L"sola"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());
	pMtrl = new AMaterial;
	pMtrl->SetName(L"m_earth");
	pMtrl->SetTexture(TEX_0, Find<ATexture>(L"earth"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());
	pMtrl = new AMaterial;
	pMtrl->SetName(L"m_mercury");
	pMtrl->SetTexture(TEX_0, Find<ATexture>(L"mercury"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());
	pMtrl = new AMaterial;
	pMtrl->SetName(L"m_venus");
	pMtrl->SetTexture(TEX_0, Find<ATexture>(L"venus"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());

	pMtrl = new AMaterial;
	pMtrl->SetName(L"m_univers");
	pMtrl->SetShader(Find<AGraphicShader>(L"Std2DShader"));
	pMtrl->SetTexture(TEX_0, Find<ATexture>(L"univers"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());

	pMtrl = new AMaterial;
	pMtrl->SetName(L"DbgMtrl");
	pMtrl->SetShader(Find<AGraphicShader>(L"DbgShader"));
	AddAsset(pMtrl->GetName(), pMtrl.Get());
}

void AssetMgr::CreateEngineSprite()
{
	Ptr<ATexture> pAtlas = FIND(ATexture, L"Link");
	float Width = pAtlas->GetWidth();
	float Height = pAtlas->GetHeight();
	Vec2 SlicePixel = Vec2(120.f, 130.f);


	Ptr<ASprite> pSprite = nullptr;
	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkMD_%d", i);

		//(SlicePixel.y / Height * 4.f) ex) 130.f / 1040.f 
		//(SlicePixel.x / Width)* i ex) i = 0 0.f, i = 1 0.1f  
		pSprite = new ASprite;
		pSprite->SetName(Buff);
		pSprite->SetAtlas(pAtlas);
		pSprite->SetLeftTopUV(Vec2((SlicePixel.x / Width) * (float)i, (SlicePixel.y / Height) * 4.f));
		pSprite->SetSliceUV(SlicePixel / Vec2(Width, Height));
		AddAsset(pSprite->GetName(), pSprite.Get());
	}

	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkML_%d", i);

		//(SlicePixel.y / Height * 4.f) ex) 130.f / 1040.f 
		//(SlicePixel.x / Width)* i ex) i = 0 0.f, i = 1 0.1f  
		pSprite = new ASprite;
		pSprite->SetName(Buff);
		pSprite->SetAtlas(pAtlas);
		pSprite->SetLeftTopUV(Vec2((SlicePixel.x / Width) * (float)i, (SlicePixel.y / Height) * 5.f));
		pSprite->SetSliceUV(SlicePixel / Vec2(Width, Height));
		AddAsset(pSprite->GetName(), pSprite.Get());
	}

	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkMU_%d", i);

		//(SlicePixel.y / Height * 4.f) ex) 130.f / 1040.f 
		//(SlicePixel.x / Width)* i ex) i = 0 0.f, i = 1 0.1f  
		pSprite = new ASprite;
		pSprite->SetName(Buff);
		pSprite->SetAtlas(pAtlas);
		pSprite->SetLeftTopUV(Vec2((SlicePixel.x / Width) * (float)i, (SlicePixel.y / Height) * 6.f));
		pSprite->SetSliceUV(SlicePixel / Vec2(Width, Height));
		AddAsset(pSprite->GetName(), pSprite.Get());
	}

	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkMR_%d", i);

		//(SlicePixel.y / Height * 4.f) ex) 130.f / 1040.f 
		//(SlicePixel.x / Width)* i ex) i = 0 0.f, i = 1 0.1f  
		pSprite = new ASprite;
		pSprite->SetName(Buff);
		pSprite->SetAtlas(pAtlas);
		pSprite->SetLeftTopUV(Vec2((SlicePixel.x / Width) * (float)i, (SlicePixel.y / Height) * 7.f));
		pSprite->SetSliceUV(SlicePixel / Vec2(Width, Height));
		AddAsset(pSprite->GetName(), pSprite.Get());
	}


	Ptr<AFlipbook> pFlipbook = nullptr;

	pFlipbook = new AFlipbook;
	pFlipbook->SetName(L"Link_MoveDown");
	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkMD_%d", i);
		pFlipbook->AddSprite(FIND(ASprite, Buff));
	}
	AddAsset(pFlipbook->GetName(), pFlipbook.Get());

	pFlipbook = new AFlipbook;
	pFlipbook->SetName(L"Link_MoveLeft");
	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkML_%d", i);
		pFlipbook->AddSprite(FIND(ASprite, Buff));
	}
	AddAsset(pFlipbook->GetName(), pFlipbook.Get());

	pFlipbook = new AFlipbook;
	pFlipbook->SetName(L"Link_MoveUp");
	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkMU_%d", i);
		pFlipbook->AddSprite(FIND(ASprite, Buff));
	}
	AddAsset(pFlipbook->GetName(), pFlipbook.Get());

	pFlipbook = new AFlipbook;
	pFlipbook->SetName(L"Link_MoveRight");
	for (int i = 0; i < 10; ++i)
	{
		wchar_t Buff[50] = {};
		swprintf_s(Buff, L"LinkMR_%d", i);
		pFlipbook->AddSprite(FIND(ASprite, Buff));
	}
	AddAsset(pFlipbook->GetName(), pFlipbook.Get());
}
