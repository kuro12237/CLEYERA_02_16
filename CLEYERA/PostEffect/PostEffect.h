#pragma once
#include"Pch.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"ViewProjection.h"
#include"CreateResource.h"
#include"GraphicsPipelineManager.h"
#include"WorldTransform.h"

class PostEffect
{
public:

	static PostEffect* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw();

private:

	uint32_t TesttexHandle = 0;
	ViewProjection viewProjection_ = {};
	WorldTransform worldTransform_ = {};

	ResourcePeroperty resource_ = {};

};
