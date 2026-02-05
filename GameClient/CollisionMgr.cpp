#include "pch.h"
#include "CollisionMgr.h"
#include "AssetMgr.h"
CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
}

void CollisionMgr::Progress(Ptr<ALevel> _Level)
{
	UINT* pMatrix = _Level->GetCllisionMatrix();

	for (UINT Row = 0; Row < MAX_LAYER; ++Row)
	{
		for (UINT Col = Row; Col < MAX_LAYER; ++Col)
		{
			// 비트 들어있는지 체크 &
			if (false == (pMatrix[Row] & (1 << Col))) continue;

			int a = 0;
			CollisionBtwLayer(_Level->GetLayer(Row), _Level->GetLayer(Col));
		}

	}
}

void CollisionMgr::CollisionBtwLayer(Layer* _Left, Layer* _Right)
{
	// & 가 붙어야 객체 복사가 안일어나고 원본 그대로 가져옴!!!!!
	// & 가 없으면 없기 때문에 지역변수로 취급함
	const vector<Ptr<GameObject>>& vecLeft = _Left->GetAllObjects();
	const vector<Ptr<GameObject>>& vecRight = _Right->GetAllObjects();

	for (UINT i = 0; i < (UINT)vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->Collider2D()) continue;

		for (UINT j = 0; j < (UINT)vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->Collider2D()) continue;

			// 두 충돌체의 고유 ID로 조합을 한 키값 생성
			COL_ID colid;
			colid.LeftID = vecLeft[i]->Collider2D()->GetId();
			colid.RightID = vecRight[j]->Collider2D()->GetId();
			
			map<ULONGLONG, bool>::iterator iter = m_mapColID.find(colid.ID);

			if (iter == m_mapColID.end())
			{
				m_mapColID.insert(make_pair(colid.ID, false));
				iter = m_mapColID.find(colid.ID);
			}
			
			if (IsCollision(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
			{
				if (iter->second)
				{
					vecLeft[i]->Collider2D()->Overlap(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->Overlap(vecLeft[i]->Collider2D());
				}
				else
				{
					vecLeft[i]->Collider2D()->BeginOverlap(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->BeginOverlap(vecLeft[i]->Collider2D());
				}
				iter->second = true;
			}
			else
			{
				if (iter->second)
				{
					vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
				}
				iter->second = false;
			}
		}
	}
}

bool CollisionMgr::IsCollision(Ptr<CCollider2D> _LeftCol, Ptr<CCollider2D> _RightCol)
{
	Ptr<AMesh> pRectMesh = FIND(AMesh,L"q");
	const Vtx* pVtx = pRectMesh->GetVtxSysMem();
	const Matrix& matWorldLeft = _LeftCol->GetWorldMatrix();
	const Matrix& matWorldRight = _RightCol->GetWorldMatrix();

	// 월드 공간상에서 충돌을 검사하기 위해서, RectMesh 모델을 각 충돌체의 월드행렬을 곱해서 정점을 충돌체 꼭지점에 배치시키낟.
	// 각 꼭지점끼리 빼서 두 충돌체의 표면 방향벡터를 각 충돌체로부터 2개씩 구한다.

	Vec4 Axis[4] = {};
	Axis[0] = XMVector2TransformCoord(pVtx[1].vPos, matWorldLeft) - XMVector2TransformCoord(pVtx[0].vPos, matWorldLeft);
	Axis[1] = XMVector2TransformCoord(pVtx[3].vPos, matWorldLeft) - XMVector2TransformCoord(pVtx[0].vPos, matWorldLeft);
	Axis[2] = XMVector2TransformCoord(pVtx[1].vPos, matWorldRight) - XMVector2TransformCoord(pVtx[0].vPos, matWorldRight);
	Axis[3] = XMVector2TransformCoord(pVtx[3].vPos, matWorldRight) - XMVector2TransformCoord(pVtx[0].vPos, matWorldRight);
	
	// 중심 벡터를 구함
	Vec3 vCenter = XMVector2TransformCoord(Vec3(0.f, 0.f, 0.f), matWorldRight) - XMVector2TransformCoord(Vec3(0.f, 0.f, 0.f), matWorldLeft);
	for (int i = 0; i < 4; ++i)
	{
		// 4 개의 축 중에서, 하나를 투영 목적지로 정함
		// 원본값을 훼손하면 나중에 투영할때 문제가 생기기 때문에, 정규화한 벡터를 따로 지역변수로 둠
		Vec3 vProjAxis = Axis[i];
		vProjAxis.Normalize(); // 투영축 정규화

		// 투영축으로 4개의 벡터를 투영시켜서 얻은 면적의 절반 길이를 구함
		float Dot = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			// 내적하는 경우 음수로 나올 수 있음 그래서 절대값을 취해줌 왜냐 코사인세타는 90가 넘어가면 음수가 됨
			Dot += fabs(vProjAxis.Dot(Axis[j])); // 내적 한 후 값을 다 더함 
		}
		Dot /= 2.f;

		// 두 충돌체의 중심끼리 이은 벡터도 투영시킴
		float fCenter = fabs(vCenter.Dot(vProjAxis)); 
		//
		if (fCenter > Dot) return false;
	}
	return true;
}
