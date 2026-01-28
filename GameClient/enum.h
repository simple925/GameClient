#pragma once
enum class CB_TYPE
{
	TRANSFORM,
	END,
};

enum class RS_TYPE
{
	CULL_BACK,	// 뒷면(정점 반시계방향으로..)
	CULL_FRONT,	// 앞면
	CULL_NONE,	// Culling X
	WIRE_FRAME,	// 정점과 정점 사이를 잇는 부분을 제외
	END,
};

enum class BS_TYPE
{
	DEFAULT,		// (SrcRGB * 1) + (DestRGB * 0)
	ALPHABLEND,		// (SrcRGB * SrcA) + (DestRGB * (1 - SrcA))
	ONE_ONE,		// (SrcRGB * 1) + (DestRGB * 1 *)
	END,
};

enum class ASSET_TYPE
{
	MESH,
	TEXTURE,
	SOUND,
	GRAPHICSHADER,
	LEVEL,
	MATERIAL,

	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,
	CAMERA,
	MESHRENDER,
	COLLIDER,
	FLIPBOOK_RENDER,
	PARTICLE_RENDER,
	LIGHT,
	TILE_RENDER,

	END,

	SCRIPT, // 여러가지 스크립트를 가지게 하기 위해서 END 뒤에 선언
};

enum class DIR
{
	RIGHT,
	UP,
	FRONT,

	END,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEX_END,
};