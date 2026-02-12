#pragma once
#include "Entity.h"

#include "ImGui/imgui.h"

class EditorUI :
	public Entity
{
private:
	string                  m_UIName;
	bool		            m_Active;
	EditorUI*				m_Parent;
	vector<Ptr< EditorUI>>  m_ChildUI;
public:
	bool IsActive() { return m_Active; }
	void SetActive(bool _Active) { m_Active = _Active; }
	void AddChildUI(Ptr<EditorUI> _Child)
	{
		_Child->m_Parent = this;
		m_ChildUI.push_back(_Child);
	}
public:
	void SetUIName(const string& _ID) { m_UIName = _ID; }
	string GetUIName() { return m_UIName; }
public:
	virtual void Tick();
	virtual void Tick_UI() = 0;
public:
	EditorUI();
	virtual ~EditorUI();
};

