#ifndef _VALUE
#define _VALUE
/*
cbuffer TRANSFORM : register(b1) // 바인딩 될 상수 레지스터 번호 (b0)
{
	float4 g_ObjectPos;
}
*/
// 꼭 버퍼가 같아야함
cbuffer MATERIAL : register(b1) // 16byte의 배수로 구성 되어야함 꼭!!!
{
	//int iArr[4]; // 16으로 봐서 16 * 4 메모리 공간임
	int g_int_0;
	int g_int_1;
	int g_int_2;
	int g_int_3;
	
	float g_float_0;
	float g_float_1;
	float g_float_2;
	float g_float_3;
	
	float2 g_vec2_0;
	float2 g_vec2_1;
	float2 g_vec2_2;
	float2 g_vec2_3;
	
	float4 g_vec4_0;
	float4 g_vec4_1;
	float4 g_vec4_2;
	float4 g_vec4_3;
	
	Matrix mat_1;
	Matrix mat_2;
};
cbuffer TRANSFORM : register(b0)
{
	//float4 g_ObjectPos;
	//float4 g_ObjectScale;
	//float4 g_ObjectRot;
	
	// row_major 행열 읽는 방식이 cpu gpu 달라서 맞춰줌
	// matrix == float4x4 같은 자료형
	row_major matrix g_matWorld; // Local(Model) -> World Space
	row_major matrix g_matView; // World -> Camea(View) Space
	row_major matrix g_matProj; // Camera(View) -> Projection Space
}
Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0); // texture 추출 도구
SamplerState g_sam_1 : register(s1); // texture 추출 도구
#endif
