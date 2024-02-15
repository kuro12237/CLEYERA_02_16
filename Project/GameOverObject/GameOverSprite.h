#pragma once
#include"Sprite/Sprite.h"

class GameOverSprite
{
public:
	GameOverSprite() {};
	~GameOverSprite() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
};

