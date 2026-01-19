#pragma once
#include "Entity.h"
class ConstBuffer :
    public Entity
{
private:
    ComPtr<ID3D11Buffer>     m_CB;
    D3D11_BUFFER_DESC       m_Desc;
    CB_TYPE                 m_Type;
public:
    int CreateBuffer(CB_TYPE _Type, UINT _Size);
    void SetData(void* _SysMem, UINT _Size);
    void Binding();
public:
    ConstBuffer();
    ~ConstBuffer();
};

