#include "pch.h"
#include "TaskMgr.h"
#include "LevelMgr.h"
#include "GameObject.h"

TaskMgr::TaskMgr()
{
}
TaskMgr::~TaskMgr()
{
}

void TaskMgr::Progress()
{
	// 쓰레기통 수거
	m_Garbage.clear();

	// Task 처리
	for (int i = 0; i < (UINT)m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			Ptr<GameObject> pNewObj = (GameObject*)m_vecTask[i].Param_0;
			Ptr<ALevel> pCurLevel = LevelMgr::GetInst()->GetLevel();
			pCurLevel->AddObject(m_vecTask[i].Param_1, pNewObj);
		}
			break;
		case TASK_TYPE::DESTROY_OBJECT:
		{
			Ptr<GameObject> pObj = (GameObject*)m_vecTask[i].Param_0;
			if (false == pObj->m_Dead) {
				pObj->m_Dead = true;
				m_Garbage.push_back(pObj);
			}
		}
			break;
		}
	}
	// 테스크를 처리하고 비움
	m_vecTask.clear();
}
