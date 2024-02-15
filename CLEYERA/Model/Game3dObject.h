#pragma once
#include"ModelManager.h"

enum ModelShaderSelect
{
	PHONG_MODEL = 0,
	UE4_BRDF = 1,
	PHONG_NORMAL_MODEL = 2,
	PHONG_SUBSURFACE_MODEL = 3
};

class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() {};

	void Create();

	void SetModel(uint32_t index);

	void Draw(WorldTransform worldTransform,ViewProjection view);


#pragma region Set

	void SetUvScale(Vector3 s) { uvScale_ = s; }
	void SetUvRotate(Vector3 r) { uvRotate = r; }
	void SetTranslate(Vector3 t) { uvTranslate = t; }

	void SetTexHandle(uint32_t index) { texHandle_ = index; }
	void SetNormalTex(uint32_t tex) { normalTexHandle_ = tex; }
	void SetBaseTex(uint32_t tex) { baseTexHandle_ = tex; }

	void UseLight(bool flag) { UseLight_ = flag; }

	void SetColor(Vector4 color) { color_ = color; }
	void SetShininess(float s) { shininess = s; }
	void SetSpecular(float s) { this->specular_ = s; };
	void SetMetalness(float m) { this->metalness_ = m; }
	void SetRoughness(float r) { this->roughness_ = r; }

	void SetlectModelPipeline(ModelShaderSelect number) { ModelShaderSelect_ = number; }

	void SetAbsorptionCoefficient_(float a) { absorptionCoefficient_ = a; }
	void SetScatterCoefficient_(float s) { scatterCoefficient_ = s; }
	void  SetScatterDistance(float s) { scatterDistance_ = s; }
#pragma endregion

private:

	Model *model_ = nullptr;
	uint32_t prevModelIndex_ = 0;

	bool CommpandPipeline(SPSOProperty &PSO);

	ComPtr<ID3D12Resource> MaterialBuffer_ = nullptr;
	Vector4 color_ = { 1,1,1,1 };
	Vector3 uvScale_ = { 1,1,1 };
	Vector3 uvRotate = { 0,0,0 };
	Vector3 uvTranslate = { 0,0,0 };
	float shininess = 70.0f;
	float specular_ = 1.0f;
	float metalness_ = 1.0f;
	float roughness_ = 1.0f;
	// 散乱係数
	float scatterCoefficient_=0.5f;
	// 吸収係数 
	float absorptionCoefficient_=0.5f;
	//光の伝播距離
	float scatterDistance_=0.5f;
	bool UseLight_ = false;

	uint32_t texHandle_ = 0;
	uint32_t normalTexHandle_ = 0;
	uint32_t baseTexHandle_ = 0;

	uint32_t ModelShaderSelect_ = 0;
};