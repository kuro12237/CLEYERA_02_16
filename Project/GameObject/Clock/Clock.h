#pragma once
#include"Game3dObject.h"

class Clock
{
public:
	static Clock* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);
private:

	static void SettingMaterial_Param();
	unique_ptr<Game3dObject>timeObj = nullptr;
	WorldTransform timePos_ = {};
	uint32_t modelHandle_ = 0;

	//
	unique_ptr<Game3dObject>needleObj = nullptr;
	WorldTransform needlePos_ = {};
	uint32_t needleHandle_ = 0;

	unique_ptr<Game3dObject>needleObj2 = nullptr;
	WorldTransform needlePos2_ = {};
	uint32_t needleHandle2_ = 0;

	float Specular_ = 0.0f;
	float metalness_ = 0.0f;
	float roughness_ = 0.0f;
	Vector4 color_ = { 1,1,1,1 };
	Vector4 color2_ = { 1,1,1,1 };
};
