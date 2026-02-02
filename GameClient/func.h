#pragma once

// Task
void CreateObject(class GameObject* _Object, int LayerIdx);


// DebugRender
void DrawDebugRect(Vec3 _Pos, Vec3 _Scale, Vec3 _Rot, Vec4 _Color, float _Duration);
void DrawDebugCircle(Vec3 _Pos, float _Radius, Vec4 _Color, float _Duration);



// 0 ~ 1 ·Î Á¦ÇÑ
float Saturate(float _Data);