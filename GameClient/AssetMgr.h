#pragma once
#include "single.h"
#include "Asset.h"
#include "PathMgr.h"

#include "AMesh.h"
#include "AGraphicShader.h"
#include "ATexture.h"
#include "AMaterial.h"

class AssetMgr
    : public singleton<AssetMgr>
{
    SINGLE(AssetMgr)
private:
    map<wstring, Ptr<Asset>>        m_mapAsset[(UINT)ASSET_TYPE::END];
public:
    void Init();
public:
    Ptr<Asset> Find(ASSET_TYPE _Type, const wstring& _Key);
    void AddAsset(const wstring& _Key, Ptr<Asset> _Asset);

    template<typename T>
    Ptr<T> Find(const wstring& _Key);
};

template<typename T>
inline Ptr<T> AssetMgr::Find(const wstring& _Key)
{
    const type_info& info = typeid(T);

    ASSET_TYPE Type = ASSET_TYPE::END;

    if (info.hash_code() == typeid(AMesh).hash_code()) {
        Type = ASSET_TYPE::MESH;
    }
    else if (info.hash_code() == typeid(AGraphicShader).hash_code()) {
        Type = ASSET_TYPE::GRAPHICSHADER;
    }
    else if (info.hash_code() == typeid(ATexture).hash_code()) {
        Type = ASSET_TYPE::TEXTURE;
    }
    else if (info.hash_code() == typeid(AMaterial).hash_code()) {
        Type = ASSET_TYPE::MATERIAL;
    }
    map<wstring, Ptr<Asset>>::iterator iter = m_mapAsset[(UINT)Type].find(_Key);
    if (iter == m_mapAsset[(UINT)Type].end()) {
        return nullptr;
    }
    return (T*)iter->second.Get();
}
