#pragma once
#include"Game3dObject.h"
class Desk
{
public:
	static Desk* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);
private:
	static void SettingMaterial_Param();
	unique_ptr<Game3dObject>DeskObj = nullptr;
	WorldTransform DeskPos_ = {};
	uint32_t modelHandle_ = 0;
	
	unique_ptr<Game3dObject>DeskObj2 = nullptr;
	WorldTransform DeskPos2_ = {};
	uint32_t modelHandle2_ = 0;
	
	
	float Specular_ = 0.0f;
	float metalness_ = 0.0f;
	float roughness_ = 0.0f;
	Vector4 color_ = { 1,1,1,1 };
};
