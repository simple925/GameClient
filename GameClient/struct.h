#pragma once

struct Vertex
{
	Vec3	vPos;	// 3D 공간상에서 정점의 위치
	Vec2	vUV;	// 정점위에 이미지를 띄울 경우, 이미지의 어느지점을 참고하는지 좌표 Texture Coordinate UV
	Vec4	vColor;	// 정점 자체의 색상
}; typedef Vertex Vtx;

struct Transform
{
	Vec4 Pos;
	Vec4 Scale;
	Vec4 Rot;
};