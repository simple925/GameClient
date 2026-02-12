#include "pch.h"
#include "LevelMgr.h"
#include "GameObject.h"
#include "AssetMgr.h"
#include "Device.h"
#include "CollisionMgr.h"

#include "CPlayerScript.h"
#include "CCamMoveScript.h"
#include "CMonsterScript.h"
#include "CStateScript.h"


LevelMgr::LevelMgr() {
}
LevelMgr::~LevelMgr() {
}
Ptr<GameObject> LevelMgr::FindObjectByName(const wstring& _name)
{
	return m_CurLevel->FindObjectByName(_name);
}
void LevelMgr::Init()
{
	// 카메라 역할 Ojbect
	Ptr<GameObject> pCameraObj = new GameObject;

	

	// Monster Object
	Ptr<GameObject> pMonster = new GameObject;

	// Player Object
	Ptr<GameObject> pObject = new GameObject;

	// Tile Object
	Ptr<GameObject> pTileObj = new GameObject;

	// Level Create
	m_CurLevel = new ALevel;
	m_CurLevel->SetName(L"Current Level");

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	m_CurLevel->GetLayer(5)->SetName(L"Enermy");
	m_CurLevel->GetLayer(6)->SetName(L"EnermyProjectile");

	/*
	* Camera Start ======================================
	*/
	//pCameraObj->SetName(L"Main Camera");
	pCameraObj->SetName(L"Main Camera");
	pCameraObj->AddComponent(new CTransform);
	pCameraObj->AddComponent(new CCamera);

	Ptr<CCamMoveScript> pCCamMoveScript = new CCamMoveScript;
	pCCamMoveScript->SetTarget(pObject);
	pCameraObj->AddComponent(pCCamMoveScript.Get());
	//pCameraObj->Camera()->LayerCheck(0); // 0번을 그려라
	pCameraObj->Camera()->LayerCheckAll(); 
	//pCameraObj->Camera()->LayerCheck(31); // 31 -> UI 레이어
	//pCameraObj->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pCameraObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCameraObj->Camera()->SetFar(10000.f);
	pCameraObj->Camera()->SetFOV(90.f);
	pCameraObj->Camera()->SetOrthoScale(1.f);

	Vec2 vResolution = Device::GetInst()->GetRenderResol();
	pCameraObj->Camera()->SetAspectRatio(vResolution.x / vResolution.y); // 종횡비(AspectRatio)
	pCameraObj->Camera()->SetWidth(vResolution.x);

	m_CurLevel->AddObject(0, pCameraObj);
	/*
	* Camera End ======================================
	*/
	
	/*
	* Light Start ======================================
	*/
	// 광원 오브젝트
	Ptr<GameObject> pLightObj = nullptr;
	/*
	*/
	pLightObj = new GameObject;
	pLightObj->SetName(L"Light_1");
	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight2D);
	//pLightObj->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light2D()->SetLightColor(Vec3(1.0f, 0.3f, 0.3f));
	//pLightObj->Light2D()->SetAmbient(Vec3(0.15f, 0.15f, 0.15f));
	pLightObj->Light2D()->SetRadius(300.f);
	pLightObj->Transform()->SetRelativePos(Vec3(-150.f, 0.f, 0.f));
	m_CurLevel->AddObject(0, pLightObj);

	pLightObj = new GameObject;
	pLightObj->SetName(L"Light_2");
	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight2D);
	//pLightObj->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light2D()->SetLightColor(Vec3(0.3f, 0.3f, 1.f));
	//pLightObj->Light2D()->SetAmbient(Vec3(0.15f, 0.15f, 0.15f));
	pLightObj->Light2D()->SetRadius(300.f);
	pLightObj->Transform()->SetRelativePos(Vec3(150.f, 0.f, 0.f));
	m_CurLevel->AddObject(0, pLightObj);
	// 광원 추가
	
	/*
	* Light End ======================================
	*/

	/*
	* Monster Start ===============================================
	*/
	pMonster->SetName(L"Monster");
	pMonster->AddComponent(new CTransform);
	pMonster->AddComponent(new CSpriteRender);
	pMonster->AddComponent(new CCollider2D);
	pMonster->Transform()->SetRelativePos(Vec3(300.f, 0.f, 100.f));
	pMonster->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 0.f));
	pMonster->SpriteRender()->SetSprite(FIND(ASprite, L"TileSprite_46"));
	m_CurLevel->AddObject(5, pMonster);
	/*
	* Monster End ===============================================
	*/

	/*
	* Player Start ===============================================
	*/
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CFlipbookRender);
	pObject->AddComponent(new CCollider2D);

	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pObject->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	pObject->Collider2D()->SetOffset(Vec2(0.f, -0.1f));
	pObject->Collider2D()->SetScale(Vec2(0.25f, 0.5f));

	pObject->FlipbookRender()->AddFlipbook(FIND(AFlipbook, L"Link_MoveDown"));
	pObject->FlipbookRender()->AddFlipbook(FIND(AFlipbook, L"Link_MoveLeft"));
	pObject->FlipbookRender()->AddFlipbook(FIND(AFlipbook, L"Link_MoveUp"));
	pObject->FlipbookRender()->AddFlipbook(FIND(AFlipbook, L"Link_MoveRight"));
	pObject->FlipbookRender()->Play(1,15.f,-1);

	Ptr<GameObject> pChild = new GameObject;
	pChild->SetName(L"Child");
	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CMeshRender);
	pChild->AddComponent(new CCollider2D);

	pChild->Transform()->SetRelativePos(Vec3(-200.f, 0.f, 0.f));
	pChild->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));
	pChild->Transform()->SetIndependentScale(true);

	pChild->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"q"));
	pChild->MeshRender()->SetMtrl(AssetMgr::GetInst()->Find<AMaterial>(L"Std2DMtrl"));

	pLightObj = new GameObject;
	pLightObj->SetName(L"Light 3");
	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight2D);

	pLightObj->Light2D()->SetLightType(LIGHT_TYPE::SPOT);
	pLightObj->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light2D()->SetRadius(400.f);
	pLightObj->Light2D()->SetAngle(XM_PI / 4.f);

	pLightObj->Transform()->SetRelativePos(pObject->Transform()->GetRelativePos());

	Ptr<CPlayerScript> playerScript = new CPlayerScript;
	playerScript->SetTarget(pMonster);
	playerScript->SetLight(pLightObj);
	pObject->AddComponent(playerScript.Get());

	// Player 와 Child 부모자식 연결
	pObject->AddChild(pChild);
	pObject->AddChild(pLightObj);
	m_CurLevel->AddObject(3, pObject);
	/*
	* Player End ===============================================
	*/


	/*
	// 오브젝트 생성
	pObject = new GameObject;
	//pObject->SetName(L"Player");
	pObject->SetName(L"sola");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CBillboardRender);
	pObject->AddComponent(new CPlayerScript);
	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));
	pObject->BillboardRender()->SetBillboardScale(Vec2(500.f, 500.f));
	pObject->BillboardRender()->SetTexture(AssetMgr::GetInst()->Find<ATexture>(L"sola"));
	m_CurLevel->AddObject(0, pObject);
	pObject = new GameObject;
	pObject->SetName(L"mercury");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CBillboardRender);
	pObject->AddComponent(new CPlanetControllerScript);
	pObject->Transform()->SetRelativePos(Vec3(100.f, 0.f, 300.f));
	pObject->BillboardRender()->SetBillboardScale(Vec2(200.f, 200.f));
	m_CurLevel->AddObject(0, pObject);

	pObject = new GameObject;
	pObject->SetName(L"earth");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CBillboardRender);
	pObject->AddComponent(new CPlanetControllerScript);
	pObject->Transform()->SetRelativePos(Vec3(200.f, 0.f, 300.f));
	pObject->BillboardRender()->SetBillboardScale(Vec2(200.f, 200.f));
	m_CurLevel->AddObject(0, pObject);

	pObject = new GameObject;
	pObject->SetName(L"venus");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CBillboardRender);
	pObject->AddComponent(new CPlanetControllerScript);
	pObject->Transform()->SetRelativePos(Vec3(300.f, 0.f, 300.f));
	pObject->BillboardRender()->SetBillboardScale(Vec2(200.f, 200.f));
	m_CurLevel->AddObject(0, pObject);
	*/

	
	/*
	* Tile Start ===============================================
	*/
	pTileObj->AddComponent(new CTransform);
	pTileObj->AddComponent(new CCollider2D);
	pTileObj->AddComponent(new CTileRender);

	pTileObj->Transform()->SetRelativePos(Vec3(-640.f, 640.f, 500.f));
	pTileObj->TileRender()->SetTileMap(FIND(ATileMap, L"TestTileMap"));

	m_CurLevel->AddObject(2, pTileObj);
	/*
	* Tile End ===============================================
	*/

	/*
	pObject = new GameObject;
	pObject->SetName(L"배경");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 1000.f));
	pObject->Transform()->SetRelativeScale(Vec3(1600.0f, 900.f, 100.f));

	pObject->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"q").Get());
	pObject->MeshRender()->SetMtrl(AssetMgr::GetInst()->Find<AMaterial>(L"m_univers"));

	m_CurLevel->AddObject(1, pObject);
	*/
	
	/*
	// 3. GameObject 생성 (3개)
	g_Object3 = new GameObject;
	g_Object3->AddComponent(new CTransform);
	g_Object3->AddComponent(new CMeshRender);
	//g_Object3->AddComponent(new CPlayerScript);

	g_Object3->Transform()->SetRelativePos(Vec3(-0.5f, 0.f, 0.f));
	g_Object3->Transform()->SetRelativeScale(Vec3(0.2f, 0.2f, 1.f)); // 반지름 역할

	g_Object3->MeshRender()->SetMesh((AMesh*)AssetMgr::GetInst()->Find<AMesh>(L"c").Get());
	g_Object3->MeshRender()->SetShader((AGraphicShader*)AssetMgr::GetInst()->Find<AGraphicShader>(L"shader2").Get());
	m_CurLevel->AddObject(0, pObject);
	*/
	//m_CurLevel->Init();

	/*
	0 Default
	1 Background
	2 Tile
	3 Player
	4 PlayerProjectile
	5 Enermy
	6 EnermyProjectile
	*/
	m_CurLevel->CheckCollisionLayer(3,5); // 나 == 적
	m_CurLevel->CheckCollisionLayer(3,6); // 나 == m탄
	m_CurLevel->CheckCollisionLayer(4,5); // p탄 == 적
	m_CurLevel->CheckCollisionLayer(5,6); // 적 == m탄
	m_CurLevel->Begin();
}

void LevelMgr::Progress()
{
	// 이전에 등록된 모든 오브젝트들 제거
	m_CurLevel->Deregister();

	// 레벨안에 있는 오브젝트들이 이번 DT 동안 할 일 수행
	m_CurLevel->Tick();
	// FinalTick 에서 행동 행위를 정산 하는 개념임
	m_CurLevel->FinalTick();

	// 충돌 검사 진행
	CollisionMgr::GetInst()->Progress(m_CurLevel);
}
