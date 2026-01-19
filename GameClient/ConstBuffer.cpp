#include "pch.h"
#include "ConstBuffer.h"
#include "Device.h"
int ConstBuffer::CreateBuffer()
{
	D3D11_BUFFER_DESC CBDesc = {};
	CBDesc.ByteWidth = sizeof(Transform);

	// cpu를 통해서 버퍼의 내용을 쓰거나, 읽을 수 있는지
	// D3D11_USAGE_DEFAULT + 0
	// 버퍼를 생성한 이후에 수정할 수 없다.
	CBDesc.Usage = D3D11_USAGE_DYNAMIC;
	CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 버퍼용도
	CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 처음 버퍼 생성할때 전달시킬 데이터의 시작주소를 Sub 구조체에 담아서 CreateBuffer 함수에 넣어준다.
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = arrVtx;
	if (FAILED(DEVICE->CreateBuffer(&CBDesc, nullptr, g_CB.GetAddressOf()))) {
		return E_FAIL;
	}
    return 0;
}

void ConstBuffer::SetData(void* _SysMem, UINT _Size)
{
}

void ConstBuffer::Binding()
{
	// 상수버퍼설정
	CONTEXT->VSSetConstantBuffers((UINT)m_Type/*상수버퍼를 바인딩할 레지스터 번호*/, 1, g_CB.GetAddressOf());
}

ConstBuffer::ConstBuffer()
{
}

ConstBuffer::~ConstBuffer()
{
}
