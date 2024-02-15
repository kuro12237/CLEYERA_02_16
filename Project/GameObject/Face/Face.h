#pragma once
#include"Game3dObject.h"
class Face
{
public:
	static Face* GetInstance();
	static void Initialize();
	static void Draw(ViewProjection view);


private:
	std::unique_ptr<Game3dObject> Fes;
	uint32_t modelHandle_ = 0;
	WorldTransform fespos;
	float Specular_ = 0.0f;
	float metalness2_ = 0.0f;
	float roughness2_ = 0.0f;
	Vector4 color2_ = { 1,1,1,1 };

	bool InitializeLock_ = false;
};
