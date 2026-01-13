#ifndef _TEST // n = not ifndef [test] test 만약 test 정의 되어있지 않다면
#define _TEST

// layout 정보
struct VS_IN
{
	// Semantic 이름에는 0이 생략 되어 있음 POSITION
	float3 vPos		: POSITION; // Semantic Layout에서 설명한 이름
	float2 vUV		: TEXCOORD;
	float4 vColor	: COLOR;
};

struct VS_OUT
{
	float4 vPosition	: SV_Position;
	float2 vUV			: TEXCOORD;
	float4 vColor		: COLOR;
};
VS_OUT VS_Test(VS_IN _input)
{
	VS_OUT output		= (VS_OUT) 0.f;
	output.vPosition	= float4(_input.vPos, 1.f);
	output.vUV			= _input.vUV;
	output.vColor		= _input.vColor;
	
	return output;
}

// 정점에서 반환한 값이 보간(Interpolation) 되어 픽셀이 쉐이더의 입력으로 돌아온다.
float4 PS_Test(VS_OUT _input) : SV_Target
{
	return _input.vColor;
	//return float4(1.f, 0.f, 0.f, 1.f);
}

#endif