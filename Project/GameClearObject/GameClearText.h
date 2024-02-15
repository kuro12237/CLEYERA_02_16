#pragma once
#include"Sprite/Sprite.h"

class GameClearText
{
public:
	GameClearText() {};
	~GameClearText() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};

};