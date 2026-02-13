#include "pch.h"
#include "AssetMgr.h"

AssetMgr::AssetMgr()
{

}
AssetMgr::~AssetMgr()
{

}

Ptr<Asset> AssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<Asset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);
	if (iter == m_mapAsset->end()) {
		return nullptr;
	}
	return iter->second;
}

void AssetMgr::AddAsset(const wstring& _Key, Ptr<Asset> _Asset)
{
	assert(m_mapAsset[(UINT)_Asset->getType()].find(_Key) == m_mapAsset[(UINT)_Asset->getType()].end());
	_Asset->SetName(_Key);
	m_mapAsset[(UINT)_Asset->getType()].insert(make_pair(_Key, _Asset));
}

void AssetMgr::GetAssetNames(ASSET_TYPE _Type, vector<wstring>& _vec)
{
	for (const auto& pair : m_mapAsset[(UINT)_Type])
	{
		_vec.push_back(pair.first);
	}
}
