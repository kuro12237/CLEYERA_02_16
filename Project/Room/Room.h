#pragma once
#include"Game3dObject.h"

class Room
{
public:
	Room() {};
	~Room() {};

	static Room *GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

	static void SetScale(float s) {
		Room::GetInstance()->worldTransofrm_.scale.x = s;
		Room::GetInstance()->worldTransofrm_.scale.y = s;
		Room::GetInstance()->worldTransofrm_.scale.z = s;

	}

private:

	static void SettingMaterial_Param();

	bool InitlializeLock_ = false;

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransofrm_ = {};
	uint32_t modelHandle_ = 0;

	float Specular_ = 0.0f;
	float metalness_ = 0.0f;
	float roughness_ = 0.0f;
	Vector4 color_ = { 1,1,1,1 };

	ModelShaderSelect modelShaderSelect_ = PHONG_MODEL ;
};