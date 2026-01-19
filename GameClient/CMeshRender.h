#pragma once
#include "Component.h"
#include "AMesh.h"
#include "AGraphicShader.h"


class CMeshRender :
    public Component
{
private:
    Ptr<AMesh>  m_Mesh;
    Ptr<AGraphicShader> m_Shader;
public:
    void SetMesh(Ptr<AMesh> _Mesh) { m_Mesh = _Mesh; }
    void SetShader(Ptr<AGraphicShader> _Shader) { m_Shader = _Shader; }
public:
    void Render();
public:
    CMeshRender();
    virtual ~CMeshRender();
};

