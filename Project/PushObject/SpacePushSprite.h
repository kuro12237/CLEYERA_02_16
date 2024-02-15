#pragma once
#include"Sprite/Sprite.h"

class SpacePushSprite
{
public:
	SpacePushSprite() {};
	~SpacePushSprite() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	WorldTransform worldTransform_ = {};
	unique_ptr<Sprite>sprite_ = nullptr;

	bool IsDraw_ = true;

	int32_t timer_ = 0;
	const int32_t kTimer_ = 60;
};