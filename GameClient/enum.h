#pragma once
enum class CB_TYPE
{
	TRANSFORM,	// b0
	MATERIAL,	// b1
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

enum class DS_TYPE
{
	LESS,				// 기본옵션 깊이가 더 가까워야 통과됨, 성공 - 깊이쓰기 0
	LESS_EQUL,			// 작거나 같으면 통과, 깊이판정 LESS_EQUAL
	NO_TEST,			// 깊이판정 X(무조건 성공)			성공 - 깊이쓰기 O
	NO_TEST_NO_WRITE,	// 깊이판정 X(무조건 성공)			성공 - 깊이쓰기 X
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
	SPRITE,
	FLIPBOOK,
	TILEMAP,
	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,
	CAMERA,
	COLLIDER2D,
	COLLIDER3D,
	LIGHT2D,
	LIGHT3D,
	MESHRENDER,
	SPRITE_RENDER,
	BILLBOARD_RENDER,
	FLIPBOOK_RENDER,
	PARTICLE_RENDER,
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

enum SCALR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
};

enum class DBG_SHAPE
{
	RECT,
	CIRCLE,

	CUBE,
	SPHERE,
};
enum class	TASK_TYPE
{
	CREATE_OBJECT,
	DESTROY_OBJECT,
};
