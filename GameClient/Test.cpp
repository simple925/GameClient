#include "pch.h"
#include "Device.h"
// 정점(vertex) 버퍼 점 세개로 하나의 면
// 정점을 저장하는 버퍼(3개의 정점을 저장시킬 예정, 삼각형을 표현하기 위해서)
ComPtr<ID3D11Buffer>		g_VB;

// InputLayout - 하나의 정점이 어떻게 구성되어 있는지에 대한 정보
ComPtr<ID3D11InputLayout>	g_Layout;

// VertexShader
// HLSL 로 작성한 VS 함수를 컴파일한 어셈블리코드를 저장시킬 버퍼
ComPtr<ID3DBlob>			g_VSBlob;
ComPtr<ID3D11VertexShader>	g_VS;



// PixelShader
ComPtr<ID3DBlob>			g_PSBlob;
ComPtr<ID3D11PixelShader>	g_PS;

int TestInit()
{
	// 상각형을 구성할 3개의 정점 기본 값 세팅
	Vtx arrVtx[3] = {};
	
	// NDC 좌표계, 중심이 0,0, 위 아래 좌 우 로 +- 1 범위
	//  __ 0 __
	// |  /|\  |
	// | / | \ |
	// |/_ | _\|
	// 2       1

	arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	arrVtx[0].vUV = Vec2(0.f,0.f);
	arrVtx[0].vColor = Vec4(1.f,0.f,0.f,0.f);

	arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	arrVtx[1].vUV = Vec2(0.f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 0.f);

	arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	arrVtx[2].vUV = Vec2(0.f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 0.f);

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


	// 처음 버퍼 생성할때 전달시킬 데이터의 시작주소를 Sub 구조체에 담아서 CreateBuffer 함수에 넣어준다.
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = arrVtx;
	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &tSub, g_VB.GetAddressOf()))) {
		return E_FAIL;
	}
	// VertexShader
	// 컴파일할 VertexShader 함수가 작성 되어있는 파일의 절대 경로
	const wchar_t* pPath = L"C:\\Users\\141245124\\Documents\\cpp\\GameClient\\GameClient\\test.fx";
	// 엔트리포인트
	if (FAILED(D3DCompileFromFile(pPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_Test", "vs_5_0", D3D10_SHADER_DEBUG, 0, g_VSBlob.GetAddressOf(), nullptr))) {
		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), nullptr, g_VS.GetAddressOf()))) {
		return E_FAIL;
	}

	if (FAILED(D3DCompileFromFile(pPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_Test", "ps_5_0", D3D10_SHADER_DEBUG, 0, g_PSBlob.GetAddressOf(), nullptr))) {
		return E_FAIL;
	}

	// 컴파일한 Shader 코드로 PixelShader 만들기
	if (FAILED(DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
		, g_PSBlob->GetBufferSize(), nullptr
		, g_PS.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ---12--- --8-- ---16---
	// Position   UV     Color
	// Input Layout 생성하기
	D3D11_INPUT_ELEMENT_DESC InputDesc[3] = {};

	InputDesc[0].SemanticName			= "POSITION";
	InputDesc[0].SemanticIndex			= 0;							// Semantic 이름이 중복되는 경우, 구별하기 위한 숫자
	InputDesc[0].AlignedByteOffset		= 0;							// 메모리 시작 위치(offset)
	InputDesc[0].Format					= DXGI_FORMAT_R32G32B32_FLOAT;	// offset 으로부터 크기
	InputDesc[0].InputSlot				= 0;							// 설명하는 정점이 들어있는 buffer의 위치
	InputDesc[0].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;	// 설명하는 정점이 들어있는 buffer의 위치
	InputDesc[0].InstanceDataStepRate	= 0;

	InputDesc[1].SemanticName = "TEXCOORD";
	InputDesc[1].SemanticIndex = 0;							// Semantic 이름이 중복되는 경우, 구별하기 위한 숫자
	InputDesc[1].AlignedByteOffset = 12;							// 메모리 시작 위치(offset)
	InputDesc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;	// offset 으로부터 크기
	InputDesc[1].InputSlot = 0;							// 설명하는 정점이 들어있는 buffer의 위치
	InputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// 설명하는 정점이 들어있는 buffer의 위치
	InputDesc[1].InstanceDataStepRate = 0;

	InputDesc[2].SemanticName = "COLOR";
	InputDesc[2].SemanticIndex = 0;							// Semantic 이름이 중복되는 경우, 구별하기 위한 숫자
	InputDesc[2].AlignedByteOffset = 20;							// 메모리 시작 위치(offset)
	InputDesc[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	// offset 으로부터 크기
	InputDesc[2].InputSlot = 0;							// 설명하는 정점이 들어있는 buffer의 위치
	InputDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	// 설명하는 정점이 들어있는 buffer의 위치
	InputDesc[2].InstanceDataStepRate = 0;

	DEVICE->CreateInputLayout(InputDesc, 3, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), g_Layout.GetAddressOf());

	return S_OK;


}

void TestTick()
{
}

void TestRender()
{
	// 이전에 그려진 그림을 지운다.
	// 랜더타겟은
	Device::GetInst()->ClearTarget();


	// HLSL(High Level Shader Language) 5.0
	// Graphic Pipeline
	// 1. IA(Input Assembler)
	// 정점을 프로그래머가 설계하기 때문에, 전달 한 버텍스 버퍼안에서, 하나의 정점의 단위크기를 알려줘야 한다.
	UINT Stride = sizeof(Vtx);
	UINT Offset = 0; // 어떤 기준위치 시작을 할지 시작점 변경값
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &Stride, &Offset);

	// 정점으로 구성할 도형의 상태, 모양
	// TriangList 는 점 3개를 이어서 만든 삼각형(내부까지 색을 채움)*****************************
	CONTEXT->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 정점 하나 안에 들어있는 데이터를 구분해주는 정보
	CONTEXT->IASetInputLayout(g_Layout.Get());

	// 랜더링에 필요한 리소스 입력
	// 2. Vertex Shader(함수) - 정점 당 연산 수행 정점쉐이더
	// HLSL(High Level 
	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);

	// 3. Rasterizer State - 정점 쉐이더에서 넘겨준 픽셀쉐이더를 호출할 함수를 연결
	// 정점쉬이더에서 반환한 정점의 취치를 NDC 좌표
	// 기준으로 들어오는 픽셀을 계산해서 픽셀 쉐이더로 연계
	// nullptr 입력: 기본 설정 옵션으로 설정
	// CULL_MODE : CULL_BACK
	// FILL_MODE : SOLID
	CONTEXT->RSSetState(nullptr);

	// 4. Pixel Shader
	// 레스터라이저를 거쳐서, 호출될 픽셀마다 실행되는 함수
	// 픽셀 쉐이더에서 리턴한 값이, 렌더타겟 내에서의 해당 픽셀 위체에 색상이 출력된다.
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	// OM (Output Merge State)
	// 픽셀 쉐이더에서 리턴한 값울, OM 단계에 연결되어있는 RenderTarget, DepthStencilTarget에 기록한다.
	// DepthStencilState - 깊이 비교	

	// 랜더링 파이프라인 시작
	// Draw 가 호출되기 전까지 설정해놓은 세팅을 기반으로 실제 렌더링 파이프라인이 실행됨
	// 그 이전까지는 각 단계별로 실행할 옵션을 설정
	CONTEXT->Draw(3, 0);
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