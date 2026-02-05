#pragma once
#include "Asset.h"
#include "ATexture.h"

// 아틀라스텍스쳐 --검색
// 인스턴싱 --검색
// 이미지 조각
class ASprite :
    public Asset
{
private:
    Ptr<ATexture>   m_Atlas;
    Vec2            m_LeftTopUV;
    Vec2            m_SliceUV;
public:
    GET_SET(Ptr<ATexture>, Atlas);
    GET_SET(Vec2, LeftTopUV);
    GET_SET(Vec2, SliceUV);
public:
    ASprite();
    virtual ~ASprite();
};

