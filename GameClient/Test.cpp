#include "pch.h"
#include "Device.h"
// 정점(vertex) 버퍼 점 세개로 하나의 면
// 정점을 저장하는 버퍼(3개의 정점을 저장시킬 예정, 삼각형을 표현하기 위해서)
ComPtr<ID3D11Buffer>		g_VB;

// InputLayout
ComPtr<ID3D11InputLayout>	g_Layout;

// VertexShader
ComPtr<ID3D11VertexShader>	g_VS;

// PixelShader
ComPtr<ID3D11PixelShader>	g_PS;



int TestInit()
{
	// 상각형을 구성할 3개의 정점 기본 값 세팅
	Vtx arrVtx[3] = {};
	
	// NDC 좌표계, 중심이 0,0 위 아래 좌 우로 +- 1 범위
	// _______
	// |  /\  |
	// | /  \ |
	// |/____\|

	arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	arrVtx[0].vUV = Vec2(0.f,0.f);
	arrVtx[0].vColor = Vec4(0.f,0.f,0.f,0.f);

	arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	arrVtx[1].vUV = Vec2(0.f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 0.f, 0.f, 0.f);

	arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	arrVtx[2].vUV = Vec2(0.f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 0.f, 0.f);

	// 정점 버터 생성
	D3D11_BUFFER_DESC VBDesc = {};

	// 버퍼 크기
	VBDesc.ByteWidth = sizeof(Vtx) * 3;

	// cpu를 통해서 버퍼의 내용을 쓰거나, 읽을 수 있는지
	// D3D11_USAGE_DYNAMIC + D3D11_CPU_ACCESS_WRITE ==> 버퍼를 생성한 이후에도, cpu를 통해서 버퍼의 내용을 수정할 수 있다.
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 버퍼용도
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	ComPtr<ID3D11Device> pDevice = Device::GetInst()->GetDevice();

	// 처음 버퍼 생성할때 전달시킬 데이터의 시작주소를 Sub 구조체에 담아서 CreateBuffer 함수에 넣어준다.
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = arrVtx;
	if (FAILED(pDevice->CreateBuffer(&VBDesc, &tSub, g_VB.GetAddressOf()))) {
		return E_FAIL;
	}
	return S_OK;
}

void TestTick()
{
}

void TestRender()
{
	// 이전에 그려진 그림을 지운다.

	// HLSL(High Level Shader Language) 5.0
	// Graphic Pipeline
	// 1. IA(Input Assembler)

	// 랜더링에 필요한 리소스 입력
	// 2. Vertex Shader(함수) - 정점 당 연산 수행 정점쉐이더

	// 3. Rasterizer State - 정점 쉐이더에서 넘겨준 픽셀쉐이더를 호출할 함수를 연결
	// 정점쉬이더에서 반환한 정점의 취치를 NDC 좌표
	// 기준으로 들어오는 픽셀을 계산해서 픽셀 쉐이더로 연계

	// 4. Pixel Shader
	// 레스터라이저를 거쳐서, 호출될 픽셀마다 실행되는 함수
	// 픽셀 쉐이더에서 리턴한 값이, 렌더타겟 내에서의 해당 픽셀 위체에 색상이 출력된다.

	// OM (Output Merge State)
	// 픽셀 쉐이더에서 리턴한 값울, OM 단계에 연결되어있는 RenderTarget, DepthStencilTarget에 기록한다.
	// DepthStencilState - 깊이 비교	
}

int TestFunc()
{
	static bool bInit = false;
	if (!bInit)
	{
		if (FAILED(TestInit()))
			return E_FAIL;

		bInit = true;
	}

	TestTick();

	TestRender();

	return S_OK;
}