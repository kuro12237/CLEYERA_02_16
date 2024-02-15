#pragma once
#include"Sprite/Sprite.h"

class BackTitleSceneSprite
{
public:
	BackTitleSceneSprite() {};
	~BackTitleSceneSprite() {};

	void Initlaize();

	void Update();

	void Draw(ViewProjection view);

private:

	uint32_t texHandle_ = 0;
	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
};
