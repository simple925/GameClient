#ifndef _DEBUG_RENDER
#define _DEBUG_RENDER

#include "value.fx"

#define COLOR g_vec4_0

// layout 정보
struct VS_IN
{
	float3 vPos : POSITION; // Semantic Layout에서 설명한 이름
	float2 vUV : TEXCOORD;
};

struct VS_OUT
{
	float4 vPosition : SV_Position; // Rasterizer 로 보낼때, NDC 좌표
	float2 vUV : TEXCOORD;
};


VS_OUT VS_Debug(VS_IN _input)
{
	/*
	// z 회전
	float3x3 rotMat =
	{
		cos(g_ObjectRot.z), sin(g_ObjectRot.z), 0.f,
		-sin(g_ObjectRot.z), cos(g_ObjectRot.z), 0.f,
		0.f, 0.f, 1.f,
	};
	// y 회전
	float3x3 rotMat =
	{
		cos(g_ObjectRot.z), 0.f, sin(g_ObjectRot.z),
		0.f, 1.f, 0.f,
		-sin(g_ObjectRot.z), 0.f, cos(g_ObjectRot.z),
	};
	// x 회전
	float3x3 rotMat =
	{
		1.f, 0.f, 0.f,
		0.f, cos(g_ObjectRot.z), sin(g_ObjectRot.z),
		0.f, -sin(g_ObjectRot.z), cos(g_ObjectRot.z),
	};
	*/

	/* 
		(x, y, z, 동차좌표)  X   ( scale.x		0		 0		 0	 )
								(	0		  scale.y	 0		 0	 )
								(	0			0	   scale.z	 0	 )
								(  pos.x	   pos.y    pos.z	 0	 )
	*/
	VS_OUT output = (VS_OUT) 0.f;
	
	// Local -> World
	float4 vWorld = mul(float4(_input.vPos, 1.f /*동차좌표*/), g_matWorld);
	// World -> View
	float4 vView = mul(vWorld, g_matView);
	// View -> Proj
	float4 vProj = mul(vView, g_matProj);
	
	// Viewz 값으로 나눈다.
	// 투영행렬 특성상, 정확한 NDC 좌표를 얻기 위해서
	// 투영행렬을 곱할 View 좌표의 z 값으로 나누는 작업이 행렬안에 있어야하는데 이것이 불가능하기 때문에
	// 연산 결과의 w(4열) 자리에 View 좌표의 z가 출력 되도록 한다.
	
	// 투영행렬을 곱하고 얻은 결과값의 x,y,z 를 w 로 나눠야 최종 NDC 좌표를 얻을 수 있다.
	// (VX, VY, VZ, 1.f) * ProjMat == (PX*VZ, PY*VZ, PZ*VZ, VZ:나눌값) 레스터라이져가 해줌
	// vProj.xyz /= vProj.w; 이 작업을 해야 NDC 좌표계로 값이 옮겨짐
	
	
	// 동차좌표 0으로 설정하면 이동 정보를 무시함
	// x,y,z, 를 w 로 나누는 작업을 Rasterizer 에서 진행하기 때문에,
	// 수동으로 나누는 코드를 작성할 필요는 없다.
	output.vPosition = vProj; // 월드행렬을 방향벡터에 곱할땐 이동정보를 무시해야되기 때문에 동차좌표가 0.f 들어가야함
	output.vUV = _input.vUV;
    
	return output;
}


float4 PS_Debug(VS_OUT _input) : SV_Target
{
	

	return COLOR;
}

#endif
