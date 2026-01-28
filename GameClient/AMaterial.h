#pragma once
#include "Asset.h"
#include "AGraphicShader.h"
#include "ATexture.h"
class AMaterial :
    public Asset
{
private:
    Ptr<AGraphicShader>     m_Shader;
    Ptr<ATexture>           m_Tex[TEX_END];

public:
    void SetTexture(TEX_PARAM _Param, Ptr<ATexture> _Texture) { m_Tex[_Param] = _Texture; }
    void Binding();
    void SetShader(Ptr<AGraphicShader> _Shader) { m_Shader = _Shader; }
public:
    AMaterial();
    virtual ~AMaterial();

};

